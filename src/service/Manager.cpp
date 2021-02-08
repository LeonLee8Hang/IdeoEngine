

#include "ideoengine/service/Manager.h"
#include "ideoengine/message/CommandClient.h"
#include "ideoengine/util/NetConnector.h"
#include "ideoengine/util/Configuration.h"
#include "ideoengine/topology/Topology.h"
#include "ideoengine/topology/TopologyLoader.h"
#include "ideoengine/task/SpoutExecutor.h"
#include "ideoengine/task/BoltExecutor.h"
#include "ideoengine/spout/ISpout.h"
#include "ideoengine/bolt/IBolt.h"
#include "ideoengine/collector/OutputCollector.h"
#include "ideoengine/collector/OutputQueue.h"
#include "ideoengine/collector/TaskQueue.h"
#include "ideoengine/base/Constants.h"
#include "logging/Logging.h"

namespace ideoengine {
namespace service {

static Manager* GlobalInstance = nullptr;

void Manager::SetGlobalInstance(Manager* manager)
{
    GlobalInstance = manager;
}

Manager* Manager::GetGlobalInstance()
{
    return GlobalInstance;
}

Manager::Manager(const ideoengine::util::Configuration& configuration) :
    CommandServer(new ideoengine::util::NetListener(ideoengine::base::NetAddress(
                                                       configuration.GetProperty(CONF_KEY_MANAGER_HOST),
                                                       configuration.GetIntegerProperty(CONF_KEY_MANAGER_PORT)))),
    _host(configuration.GetProperty(CONF_KEY_MANAGER_HOST)),
    _port(configuration.GetIntegerProperty(CONF_KEY_MANAGER_PORT)) {
    _managerConfiguration.reset(new ideoengine::util::Configuration(configuration));
    _name = configuration.GetProperty(CONF_KEY_MANAGER_NAME);

    InitPresidentConnector();
    InitSelfContext();
    ReserveExecutors();
    InitEvents();
}

void Manager::InitPresidentConnector()
{
    ideoengine::base::NetAddress presidentAddress(_managerConfiguration->GetProperty(CONF_KEY_PRESIDENT_PORT),
                                                 _managerConfiguration->GetIntegerProperty(CONF_KEY_PRESIDENT_PORT));
    _presidentConnector = new ideoengine::util::NetConnector(presidentAddress);
    _presidentClient = new ideoengine::message::CommandClient(_presidentConnector);
}

void Manager::ReserveExecutors()
{
    _spoutExecutors.resize(_managerConfiguration->GetIntegerProperty(CONF_KEY_SPOUT_COUNT));
    _boltExecutors.resize(_managerConfiguration->GetIntegerProperty(CONF_KEY_BOLT_COUNT));
    _spoutCollectors.resize(_managerConfiguration->GetIntegerProperty(CONF_KEY_SPOUT_COUNT));
    _boltCollectors.resize(_managerConfiguration->GetIntegerProperty(CONF_KEY_BOLT_COUNT));
    _boltTaskQueues.resize(_managerConfiguration->GetIntegerProperty(CONF_KEY_BOLT_COUNT));

    for ( auto& boltTask : _boltTaskQueues ) {
        boltTask.reset(new collector::TaskQueue);
    }

    _outputDispatcher.SetQueue(std::shared_ptr<collector::OutputQueue>(
                                   new collector::OutputQueue()));
    _outputDispatcher.SetSelfAddress(ideoengine::base::NetAddress(_host, _port));
    _outputDispatcher.SetSelfTasks(_boltTaskQueues);
    _outputDispatcher.SetSelfSpoutCount(static_cast<int32_t>(_spoutExecutors.size()));

    ideoengine::base::NetAddress presidentAddress(
                _managerConfiguration->GetProperty(CONF_KEY_PRESIDENT_HOST),
                _managerConfiguration->GetIntegerProperty(CONF_KEY_PRESIDENT_PORT));
    _presidentConnector = new ideoengine::util::NetConnector(presidentAddress);
    _presidentClient = new ideoengine::message::CommandClient(_presidentConnector);
    _outputDispatcher.SetPresidentClient(_presidentClient);

    _outputDispatcher.Start();
}

void Manager::InitEvents()
{
    OnConnection(std::bind(&Manager::OnConnect, this, std::placeholders::_1));
    OnCommand(ideoengine::message::Command::Type::Heartbeat, this, &Manager::OnHeartbeat);
    OnCommand(ideoengine::message::Command::Type::SyncMetadata, this, &Manager::OnSyncMetadata);
    OnCommand(ideoengine::message::Command::Type::SendTuple, this, &Manager::OnSendTuple);
}

void Manager::InitTaskFieldsMap()
{
    const std::map<std::string, ideoengine::spout::SpoutDeclarer>& spoutDeclarers =
            _topology->GetSpoutDeclarers();
    for ( const auto& spoutDeclarerPair : spoutDeclarers ) {
        const spout::SpoutDeclarer& spoutDeclarer = spoutDeclarerPair.second;

        _taskFields[spoutDeclarer.GetTaskName()] = &spoutDeclarer.GetFields();
        _taskFieldsMap[spoutDeclarer.GetTaskName()] = &spoutDeclarer.GetFieldsMap();
    }

    const std::map<std::string, ideoengine::bolt::BoltDeclarer>& boltDeclarers =
            _topology->GetBoltDeclarers();
    for ( const auto& boltDeclarerPair : boltDeclarers ) {
        const bolt::BoltDeclarer& boltDeclarer = boltDeclarerPair.second;

        _taskFields[boltDeclarer.GetTaskName()] = &boltDeclarer.GetFields();
        _taskFieldsMap[boltDeclarer.GetTaskName()] = &boltDeclarer.GetFieldsMap();
    }

    _outputDispatcher.SetTaskFields(_taskFields);
    _outputDispatcher.SetTaskFieldsMap(_taskFieldsMap);
}

void Manager::OnConnect(ManagerContext* context) {
}

void Manager::JoinPresident(JoinPresidentCallback callback) {
    ideoengine::message::CommandClient* commandClient = _presidentClient;

    _presidentConnector->Connect([commandClient, callback, this](const util::SocketError&) {
        ideoengine::message::Command command(ideoengine::message::Command::Type::Join);
        command.AddArgument({ NODE_MANAGER });
        command.AddArgument({ this->_host });
        command.AddArgument({ this->_port });
        std::vector<ideoengine::base::Variant> context;
        _selfContext->Serialize(context);
        command.AddArguments(context);

        commandClient->SendCommand(command, [callback](const ideoengine::message::Response& response,
                                   const message::CommandError& error) {
            if ( error.GetType() != message::CommandError::Type::NoError ) {
                LOG(LOG_ERROR) << error.what();
                return;
            }

            callback(response);
        });
    });
}

void Manager::OnHeartbeat(ManagerContext* context, const message::Command& command,
                          ideoengine::message::CommandServer<ideoengine::message::BaseCommandServerContext>::Responsor Responsor)
{
    ideoengine::message::Response response(ideoengine::message::Response::Status::Successful);
    response.AddArgument({ _name });

    Responsor(response);
}

void Manager::OnSyncMetadata(ManagerContext* context, const message::Command& command,
                             message::CommandServer<ideoengine::message::BaseCommandServerContext>::Responsor Responsor)
{
    const std::vector<ideoengine::base::Variant>& arguments = command.GetArguments();

    int32_t syncMethod = arguments[0].GetInt32Value();
    if ( syncMethod != 1 ) {
        ideoengine::message::Response response(ideoengine::message::Response::Status::Failed);
        Responsor(response);

        return;
    }

    ideoengine::message::Response response(ideoengine::message::Response::Status::Successful);
    base::Variants::const_iterator currentIterator = arguments.cbegin() + 1;
    _selfContext->Deserialize(currentIterator);

    OwnManagerTasks();
    _outputDispatcher.SetTaskInfos(_selfContext->GetTaskInfos());

    ShowManagerMetadata();
    ShowTaskInfos();

    std::string topologyName = _managerConfiguration->GetProperty(CONF_KEY_TOPOLOGY_NAME);
    _topology = ideoengine::topology::TopologyLoader::GetInstance().GetTopology(topologyName);

    InitTaskFieldsMap();
    InitExecutors();

    Responsor(response);
}

void Manager::OnSendTuple(ManagerContext* context, const message::Command& command,
                          message::CommandServer<ideoengine::message::BaseCommandServerContext>::Responsor Responsor)
{
    const base::Variants& arguments = command.GetArguments();
    base::Variants::const_iterator it = arguments.cbegin();

    base::NetAddress sourceAddress;
    sourceAddress.Deserialize(it);

    task::ExecutorPosition destination;
    destination.Deserialize(it);

    base::Tuple tuple;
    tuple.Deserialize(it);
    tuple.SetFields(_taskFields[tuple.GetSourceTask()]);
    tuple.SetFieldsMap(_taskFieldsMap[tuple.GetSourceTask()]);

    int32_t executorIndex = destination.GetExecutorIndex();
    int32_t boltIndex = executorIndex - _selfContext->GetSpoutCount();

    std::shared_ptr<ideoengine::collector::TaskQueue> taskQueue = _boltTaskQueues[boltIndex];
    collector::TaskItem* taskItem =
            new collector::TaskItem(executorIndex, tuple);
    taskQueue->Push(taskItem);

    ideoengine::message::Response response(ideoengine::message::Response::Status::Successful);
    Responsor(response);
}

ideoengine::message::CommandClient* Manager::CreatePresidentClient()
{
    ideoengine::base::NetAddress presidentAddress(_managerConfiguration->GetProperty(CONF_KEY_PRESIDENT_PORT),
                                                 _managerConfiguration->GetIntegerProperty(CONF_KEY_PRESIDENT_PORT));
    ideoengine::util::NetConnector* presidentConnector =
            new ideoengine::util::NetConnector(presidentAddress);
    ideoengine::message::CommandClient* presidentClient =
            new ideoengine::message::CommandClient(presidentConnector);

    return presidentClient;
}

std::string Manager::GetTopologyName() const
{
    return _topology->GetName();
}

void Manager::InitSelfContext() {
    this->_selfContext.reset(new ManagerContext);
    _selfContext->SetId(_name);
    _selfContext->SetSpoutCount(_managerConfiguration->GetIntegerProperty(CONF_KEY_SPOUT_COUNT));
    _selfContext->SetBoltCount(_managerConfiguration->GetIntegerProperty(CONF_KEY_BOLT_COUNT));
    _selfContext->SetTaskInfos(std::vector<ideoengine::task::TaskInfo>(_selfContext->GetSpoutCount() + _selfContext->GetBoltCount()));

    std::set<int32_t> freeSpouts;
    int spoutCount = _selfContext->GetSpoutCount();
    for ( int32_t spoutIndex = 0; spoutIndex != spoutCount; ++ spoutIndex ) {
        freeSpouts.insert(spoutIndex);
    }
    _selfContext->SetFreeSpouts(freeSpouts);

    std::set<int32_t> freeBolts;
    int boltCount = _selfContext->GetBoltCount();
    for ( int32_t boltIndex = 0; boltIndex != boltCount; ++ boltIndex ) {
        freeBolts.insert(boltIndex);
    }
    _selfContext->SetFreeBolts(freeBolts);
}

void Manager::InitSpoutExecutors()
{
    LOG(LOG_DEBUG) << "Init spout executors";
    const std::map<std::string, ideoengine::spout::SpoutDeclarer>& spoutDeclarers =
            _topology->GetSpoutDeclarers();
    std::set<int32_t> busySpouts = _selfContext->GetBusySpouts();
    for ( int32_t spoutIndex : busySpouts ) {
        ideoengine::task::TaskInfo& spoutTask = _selfContext->GetSpoutTaskInfo(spoutIndex);
        std::string taskName = spoutTask.GetTaskName();
        const ideoengine::spout::SpoutDeclarer& spoutDeclarer = spoutDeclarers.at(taskName);

        std::shared_ptr<collector::OutputQueue> outputQueue = _outputDispatcher.GetQueue();
        collector::OutputCollector* collector = new collector::OutputCollector(spoutIndex,
                                                                               taskName, outputQueue);
        _spoutCollectors[spoutIndex].reset(collector);

        spout::ISpout* spout = spoutDeclarer.GetSpout()->Clone();
        spout->Prepare(_spoutCollectors[spoutIndex]);

        std::shared_ptr<task::SpoutExecutor> spoutExecutor(new task::SpoutExecutor);
        spoutExecutor->SetSpout(spout);
        int32_t flowParam = _managerConfiguration->GetIntegerProperty(CONF_KEY_SPOUT_FLOW_PARAM);
        spoutExecutor->SetFlowParam(flowParam);
        _spoutExecutors[spoutIndex] = spoutExecutor;
    }
}

void Manager::InitBoltExecutors()
{
    LOG(LOG_DEBUG) << "Init bolt executors";
    const std::map<std::string, ideoengine::bolt::BoltDeclarer>& boltDeclarers =
            _topology->GetBoltDeclarers();
    std::set<int32_t> busyBolts = _selfContext->GetBusyBolts();
    int32_t spoutCount = _selfContext->GetSpoutCount();
    for ( int32_t boltIndex : busyBolts ) {
        LOG(LOG_DEBUG) << boltIndex;

        ideoengine::task::TaskInfo& boltTask = _selfContext->GetBoltTaskInfo(boltIndex);
        std::string taskName = boltTask.GetTaskName();
        const ideoengine::bolt::BoltDeclarer& boltDeclarer = boltDeclarers.at(taskName);

        std::shared_ptr<collector::OutputQueue> outputQueue = _outputDispatcher.GetQueue();
        collector::OutputCollector* collector = new collector::OutputCollector(
                    spoutCount + boltIndex, taskName, outputQueue);
        _boltCollectors[boltIndex].reset(collector);

        bolt::IBolt* bolt = boltDeclarer.GetBolt()->Clone();
        bolt->Prepare(_boltCollectors[boltIndex]);

        std::shared_ptr<task::BoltExecutor> boltExecutor(new task::BoltExecutor);
        _boltExecutors[boltIndex] = boltExecutor;
        boltExecutor->SetTaskQueue(_boltTaskQueues[boltIndex]);
        boltExecutor->SetBolt(bolt);
    }
}

void Manager::InitExecutors()
{
    InitSpoutExecutors();
    InitBoltExecutors();

    std::set<int32_t> busyBolts = _selfContext->GetBusyBolts();
    std::set<int32_t> busySpouts = _selfContext->GetBusySpouts();

    for ( int32_t boltIndex : busyBolts ) {
        _boltExecutors[boltIndex]->Start();
    }

    for ( int32_t spoutIndex : busySpouts ) {
        _spoutExecutors[spoutIndex]->Start();
    }
}

void Manager::OwnManagerTasks()
{
    std::vector<ideoengine::task::TaskInfo>& taskInfos = _selfContext->GetTaskInfos();
    for ( ideoengine::task::TaskInfo& taskInfo : taskInfos ) {
        taskInfo.SetManagerContext(_selfContext.get());
    }
}

void Manager::ShowManagerMetadata()
{
    LOG(LOG_DEBUG) << "Manager name: " << _selfContext->GetId();
    LOG(LOG_DEBUG) << "  Spout count: " << _selfContext->GetSpoutCount();
    LOG(LOG_DEBUG) << "  Bolt count: " << _selfContext->GetBoltCount();
    LOG(LOG_DEBUG) << "  Task info count: " << _selfContext->GetTaskInfos().size();
    LOG(LOG_DEBUG) << "  Free spout count: " << _selfContext->GetFreeSpouts().size();
    LOG(LOG_DEBUG) << "  Free bolt count: " << _selfContext->GetFreeBolts().size();
    LOG(LOG_DEBUG) << "  Busy spout count: " << _selfContext->GetBusySpouts().size();
    LOG(LOG_DEBUG) << "  Busy bolt count: " << _selfContext->GetBusyBolts().size();
}

void Manager::ShowTaskInfos()
{
    const std::vector<ideoengine::task::TaskInfo>& taskInfos = _selfContext->GetTaskInfos();
    for ( const ideoengine::task::TaskInfo& taskInfo : taskInfos ) {
        if ( !taskInfo.GetManagerContext() ) {
            continue;
        }

        LOG(LOG_DEBUG) << "    Manager: " << taskInfo.GetManagerContext()->GetId();
        LOG(LOG_DEBUG) << "    Exectuor index: " << taskInfo.GetExecutorIndex();
        LOG(LOG_DEBUG) << "    Task name: " << taskInfo.GetTaskName();
        LOG(LOG_DEBUG) << "    Paths: ";
        const std::list<ideoengine::task::PathInfo>& paths = taskInfo.GetPaths();

        for ( const ideoengine::task::PathInfo& path : paths ) {
            LOG(LOG_DEBUG) << "      Path: ";
            int32_t groupMethod = path.GetGroupMethod();
            LOG(LOG_DEBUG) << "        Group method: " << groupMethod;

            if ( path.GetGroupMethod() == ideoengine::task::PathInfo::GroupMethod::Global) {
                LOG(LOG_DEBUG) << "        Destination host: " <<
                                  path.GetDestinationExecutors()[0].GetManager().GetHost();
                LOG(LOG_DEBUG) << "        Destination port: " <<
                                  path.GetDestinationExecutors()[0].GetManager().GetPort();
                LOG(LOG_DEBUG) << "        Destination executor index: " <<
                                  path.GetDestinationExecutors()[0].GetExecutorIndex();
            }
        }
    }
}
}
}

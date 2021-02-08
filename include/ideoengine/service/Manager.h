

#pragma once

#include "ideoengine/message/CommandServer.h"
#include "ideoengine/util/NetListener.h"
#include "ideoengine/base/NetAddress.h"
#include "ideoengine/service/ManagerContext.h"
#include "ideoengine/collector/OutputDispatcher.h"

#include <functional>
#include <memory>

namespace ideoengine {
namespace util {
class NetConnector;
class Configuration;
}

namespace message {
class CommandClient;
}

namespace task {
class SpoutExecutor;
class BoltExecutor;
}

namespace topology {
class Topology;
}

namespace collector {
class OutputCollector;
class TaskQueue;
}

namespace service {
class Manager : public ideoengine::message::CommandServer<ManagerContext> {
public:
    static void SetGlobalInstance(Manager* manager);
    static Manager* GetGlobalInstance();

    typedef std::function<void(const ideoengine::message::Response& response)> JoinPresidentCallback;

    Manager(const ideoengine::util::Configuration& configuration);

    void OnConnect(ManagerContext* context);

    void JoinPresident(JoinPresidentCallback callback);

    void OnHeartbeat(ManagerContext* context, const ideoengine::message::Command& command,
                     ideoengine::message::CommandServer<ideoengine::message::BaseCommandServerContext>::Responsor Responsor);
    void OnSyncMetadata(ManagerContext* context, const ideoengine::message::Command& command,
                        ideoengine::message::CommandServer<ideoengine::message::BaseCommandServerContext>::Responsor Responsor);
    void OnSendTuple(ManagerContext* context, const ideoengine::message::Command& command,
                     ideoengine::message::CommandServer<ideoengine::message::BaseCommandServerContext>::Responsor Responsor);

    message::CommandClient* CreatePresidentClient();
    std::string GetTopologyName() const;

private:
    void InitSelfContext();
    void InitExecutors();
    void OwnManagerTasks();
    void ShowManagerMetadata();
    void ShowTaskInfos();
    void InitSpoutExecutors();
    void InitBoltExecutors();
    void InitPresidentConnector();
    void ReserveExecutors();
    void InitEvents();
    void InitTaskFieldsMap();

private:
    std::string _name;
    std::string _host;
    int32_t _port;
    std::shared_ptr<ideoengine::util::Configuration> _managerConfiguration;
    ideoengine::util::NetConnector* _presidentConnector;
    ideoengine::message::CommandClient* _presidentClient;
    std::shared_ptr<ideoengine::service::ManagerContext> _selfContext;
    std::vector<std::shared_ptr<ideoengine::task::SpoutExecutor>> _spoutExecutors;
    std::vector<std::shared_ptr<ideoengine::task::BoltExecutor>> _boltExecutors;
    std::vector<std::shared_ptr<ideoengine::collector::OutputCollector>> _spoutCollectors;
    std::vector<std::shared_ptr<ideoengine::collector::OutputCollector>> _boltCollectors;
    std::vector<std::shared_ptr<ideoengine::collector::TaskQueue>> _boltTaskQueues;
    std::shared_ptr<topology::Topology> _topology;
    ideoengine::collector::OutputDispatcher _outputDispatcher;
    std::map<std::string, const std::vector<std::string>*> _taskFields;
    std::map<std::string, const std::map<std::string, int32_t>*> _taskFieldsMap;
};
}
}

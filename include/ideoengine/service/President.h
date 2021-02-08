#pragma once

#include "ideoengine/message/CommandServer.h"
#include "ideoengine/util/NetListener.h"
#include "ideoengine/base/NetAddress.h"
#include "ideoengine/service/ManagerContext.h"

#include <thread>

namespace ideoengine {
namespace util {
class Configuration;
}

namespace topology {
class Topology;
}

namespace message {
class CommandClient;
}

namespace spout {
class SpoutDeclarer;
}

namespace bolt {
class BoltDeclarer;
}

namespace service {
typedef std::pair<std::string, std::string> TaskPathName;

class President : public ideoengine::message::CommandServer<ManagerContext> {
public:
    President(const ideoengine::base::NetAddress& host);
    President(const ideoengine::util::Configuration& configuration);

    void OnConnect(ManagerContext* context);
    void OnJoin(ManagerContext* context, const ideoengine::message::Command& command,
                ideoengine::message::CommandServer<ideoengine::message::BaseCommandServerContext>::Responsor Responsor);
    void OnAskField(ManagerContext* context, const ideoengine::message::Command& command,
                    ideoengine::message::CommandServer<ideoengine::message::BaseCommandServerContext>::Responsor Responsor);
    void OnOrderId(ManagerContext* context, const ideoengine::message::Command& command,
                   ideoengine::message::CommandServer<ideoengine::message::BaseCommandServerContext>::Responsor Responsor);
    void SubmitTopology(ideoengine::topology::Topology* topology);

private:
    void SendHeartbeat(const std::string managerId, int32_t sendTimes);
    std::list<ideoengine::task::TaskInfo> GetAllSpoutTasks(const std::map<std::string, ideoengine::spout::SpoutDeclarer>& spoutDeclarers, ideoengine::topology::Topology* topology);
    void AllocateSpoutTasks(std::map<std::string, ideoengine::task::TaskInfo*> nameToSpoutTasks, std::list<ideoengine::task::TaskInfo> originSpoutTasks);
    std::map<std::string, std::vector<task::TaskInfo*> > AllocateSpoutTasks(std::list<task::TaskInfo>& originSpoutTasks);
    std::list<ideoengine::task::TaskInfo> GetAllBoltTasks(ideoengine::topology::Topology* topology, const std::map<std::string, ideoengine::bolt::BoltDeclarer>& boltDeclarers);
    std::map<std::string, std::vector<task::TaskInfo*> > AllocateBoltTasks(std::list<task::TaskInfo>& originBoltTasks);
    std::vector<task::TaskInfo*> FindTask(
            const std::map<std::string, std::vector<task::TaskInfo*> >& nameToBoltTasks,
            const std::map<std::string, std::vector<task::TaskInfo*> >& nameToSpoutTasks,
            const std::string& sourceTaskName);
    std::vector<task::TaskInfo*> FindTask(
            const std::map<std::string, std::vector<task::TaskInfo*> >& nameToBoltTasks,
            const std::string& sourceTaskName);
    void CalculateTaskPaths(
            const std::map<std::string, std::vector<task::TaskInfo*> >& nameToBoltTasks,
            const std::map<std::string, ideoengine::bolt::BoltDeclarer>& boltDeclarers,
            const std::map<std::string, std::vector<task::TaskInfo*> >& nameToSpoutTasks);
    void ShowManagerMetadata();
    void ShowManagerTaskInfos();
    void ShowTaskInfos(const std::vector<ideoengine::task::TaskInfo>& taskInfos);
    void SyncWithManagers();
    void StartConnectionChecker();
    void CheckConnections();

private:
    ideoengine::base::NetAddress _presidentHost;
    std::vector<ManagerContext> _managers;
    int32_t _managerCount;
    std::shared_ptr<ideoengine::util::Configuration> _configuration;
    std::map<std::string, std::shared_ptr<ideoengine::message::CommandClient>> _managerClients;
    std::map<TaskPathName, std::vector<task::ExecutorPosition>> _fieldsCandidates;
    std::map<TaskPathName, std::map<std::string, task::ExecutorPosition>> _fieldsDestinations;
    std::map<std::string, int64_t> _orderIds;
    bool _submitted;

    std::thread _connectionChecker;
};
}
}

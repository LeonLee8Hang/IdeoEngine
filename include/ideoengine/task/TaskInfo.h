

#pragma once

#include "ideoengine/base/NetAddress.h"
#include "ideoengine/base/Variant.h"
#include <string>
#include <cstdint>
#include <list>
#include <map>

namespace ideoengine {
namespace service {
class ManagerContext;
}

namespace task {
class ExecutorPosition : public ideoengine::base::Serializable {
public:
    ExecutorPosition();
    ExecutorPosition(const ideoengine::base::NetAddress& manager, int32_t executorIndex);

    const ideoengine::base::NetAddress& GetManager() const {
        return _manager;
    }

    void SetManager(const ideoengine::base::NetAddress& manager) {
        _manager = manager;
    }

    int32_t GetExecutorIndex() const {
        return _executorIndex;
    }

    void SetExecutorIndex(int32_t executorIndex) {
        _executorIndex = executorIndex;
    }

    virtual void Serialize(ideoengine::base::Variants& variants) const override;
    virtual void Deserialize(ideoengine::base::Variants::const_iterator& it) override;

private:
    ideoengine::base::NetAddress _manager;
    int32_t _executorIndex;
};

class PathInfo : public ideoengine::base::Serializable {
public:
    struct GroupMethod {
        enum {
            Invalid = 0,
            Global,
            Field,
            Random
        };
    };

    PathInfo();

    int32_t GetGroupMethod() const {
        return _groupMethod;
    }

    void SetGroupMethod(int32_t groupMethod) {
        _groupMethod = groupMethod;
    }

    void SetDestinationTask(const std::string& taskName) {
        _destinationTask = taskName;
    }

    const std::string& GetTaskName() const {
        return _destinationTask;
    }

    const std::string& GetFieldName() const {
        return _fieldName;
    }

    void SetFieldName(const std::string& fieldName) {
        _fieldName = fieldName;
    }

    const std::vector<ExecutorPosition>& GetDestinationExecutors() const {
        return _destinationExecutors;
    }

    void SetDestinationExecutors(const std::vector<ExecutorPosition>& executors) {
        _destinationExecutors = executors;
    }

    virtual void Serialize(ideoengine::base::Variants& variants) const override;
    virtual void Deserialize(ideoengine::base::Variants::const_iterator& it) override;

private:
    int32_t _groupMethod;
    std::string _destinationTask;
    std::string _fieldName;
    std::vector<ExecutorPosition> _destinationExecutors;
};

class TaskInfo : public ideoengine::base::Serializable {
public:
    TaskInfo();

    const std::string& GetTopologyName() const {
        return _topologyName;
    }

    void SetTopologyName(const std::string& topologyName) {
        _topologyName = topologyName;
    }

    const std::string& GetTaskName() const {
        return _taskName;
    }

    void SetTaskName(const std::string& taskName) {
        _taskName = taskName;
    }

    const std::list<PathInfo>& GetPaths() const {
        return _paths;
    }

    void SetPaths(const std::list<PathInfo>& paths) {
        _paths = paths;
    }

    void AddPath(const PathInfo& path) {
        _paths.push_back(path);
    }

    const ideoengine::service::ManagerContext* GetManagerContext() const {
        return _managerContext;
    }

    ideoengine::service::ManagerContext* GetManagerContext() {
        return _managerContext;
    }

    void SetManagerContext(ideoengine::service::ManagerContext* context) {
        _managerContext = context;
    }

    int32_t GetExecutorIndex() const {
        return _executorIndex;
    }

    void SetExecutorIndex(int32_t executorIndex) {
        _executorIndex = executorIndex;
    }

    virtual void Serialize(ideoengine::base::Variants& variants) const override;
    virtual void Deserialize(ideoengine::base::Variants::const_iterator& it) override;

    std::string _topologyName;
    std::string _taskName;
    std::list<PathInfo> _paths;

    ideoengine::service::ManagerContext* _managerContext;
    int32_t _executorIndex;
};
}
}

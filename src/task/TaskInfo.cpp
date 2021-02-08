

#include "ideoengine/task/TaskInfo.h"

namespace ideoengine {
namespace task {

using ideoengine::base::Variant;
using ideoengine::base::Variants;
using ideoengine::base::Serializable;

ExecutorPosition::ExecutorPosition() : _executorIndex(-1) {
}

ExecutorPosition::ExecutorPosition(const ideoengine::base::NetAddress& manager, int32_t executorIndex) :
    _manager(manager), _executorIndex(executorIndex) {
}

PathInfo::PathInfo() : _groupMethod(GroupMethod::Invalid) {}

TaskInfo::TaskInfo() : _managerContext(nullptr), _executorIndex(-1) {
}

void TaskInfo::Serialize(base::Variants& variants) const
{
    Variant::Serialize(variants, _topologyName);
    Variant::Serialize(variants, _taskName);
    Variant::Serialize(variants, _paths);
    Variant::Serialize(variants, _executorIndex);
}

void TaskInfo::Deserialize(base::Variants::const_iterator& it)
{
    Variant::Deserialize(it, _topologyName);
    Variant::Deserialize(it, _taskName);
    Variant::Deserialize(it, _paths);
    Variant::Deserialize(it, _executorIndex);
}

}
}

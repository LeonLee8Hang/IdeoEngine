

#include "ideoengine/task/TaskInfo.h"
#include "ideoengine/base/Variant.h"

namespace ideoengine {
namespace task {

using ideoengine::base::Variant;
using ideoengine::base::Variants;
using ideoengine::base::Serializable;

void PathInfo::Serialize(base::Variants& variants) const
{
    Variant::Serialize(variants, _groupMethod);
    Variant::Serialize(variants, _destinationTask);
    Variant::Serialize(variants, _fieldName);
    Variant::Serialize(variants, _destinationExecutors);
}

void PathInfo::Deserialize(Variants::const_iterator& it)
{
    Variant::Deserialize(it, _groupMethod);
    Variant::Deserialize(it, _destinationTask);
    Variant::Deserialize(it, _fieldName);
    Variant::Deserialize(it, _destinationExecutors);
}

void ExecutorPosition::Serialize(base::Variants& variants) const
{
    Variant::Serialize(variants, _manager);
    Variant::Serialize(variants, _executorIndex);
}

void ExecutorPosition::Deserialize(Variants::const_iterator& it)
{
    Variant::Deserialize(it, _manager);
    Variant::Deserialize(it, _executorIndex);
}

}
}

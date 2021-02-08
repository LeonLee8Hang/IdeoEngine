

#include "ideoengine/task/TaskDeclarer.h"

namespace ideoengine {
namespace task {

TaskDeclarer::TaskDeclarer() :
    _type(Type::Invalid), _groupMethod(GroupMethod::Global), _parallismHint(1) {
}

}
}

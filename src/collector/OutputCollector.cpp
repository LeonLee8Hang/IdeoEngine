

#include "ideoengine/collector/OutputCollector.h"
#include "ideoengine/collector/OutputQueue.h"
#include "ideoengine/base/Values.h"

#include <iostream>

namespace ideoengine {
namespace collector {

OutputCollector::OutputCollector() : _taskIndex(-1) {}

OutputCollector::OutputCollector(
        int32_t taskIndex, const std::string& taskName, std::shared_ptr<OutputQueue> queue) :
    _taskIndex(taskIndex), _taskName(taskName), _queue(queue) {
}

void OutputCollector::Emit(const ideoengine::base::Tuple& tuple) {
    if ( _taskIndex != -1 ) {
        _queue->Push(new OutputItem(_taskIndex, tuple, _taskName));
    }
}

}
}

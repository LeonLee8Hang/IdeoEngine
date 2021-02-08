#pragma once

namespace ideoengine {
namespace collector {

OutputItem::OutputItem(int32_t taskIndex, const base::Tuple& tuple, const std::string& taskName) :
    _taskIndex(taskIndex), _tuple(tuple) {
    _tuple.SetSourceTask(taskName);
}

}
}

#pragma once

namespace ideoengine {
namespace collector {

TaskItem::TaskItem(int32_t taskIndex, const base::Tuple& tuple) :
    _taskIndex(taskIndex), _tuple(tuple) {
}

}
}

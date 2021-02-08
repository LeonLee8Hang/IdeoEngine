#pragma once

#include "ideoengine/base/BlockingQueue.h"
#include "ideoengine/base/Values.h"

namespace ideoengine {
namespace collector {

class TaskItem {
public:
    inline TaskItem(int32_t taskIndex, const base::Tuple& tuple);

    int32_t GetTaskIndex() const {
        return _taskIndex;
    }

    const base::Tuple& GetTuple() const {
        return _tuple;
    }

private:
    int32_t _taskIndex;
    base::Tuple _tuple;
};

class TaskQueue : public base::BlockingQueue<TaskItem*> {
};

}
}

#include "ideoengine/collector/TaskItem.tcc"

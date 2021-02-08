#pragma once

#include "ideoengine/base/BlockingQueue.h"
#include "ideoengine/base/Values.h"

namespace ideoengine {
namespace collector {

class OutputItem {
public:
    inline OutputItem(int32_t taskIndex, const base::Tuple& tuple, const std::string& taskName);

    int32_t GetTaskIndex() const {
        return _taskIndex;
    }

    base::Tuple& GetTuple() {
        return _tuple;
    }

    const base::Tuple& GetTuple() const {
        return _tuple;
    }

private:
    int32_t _taskIndex;
    base::Tuple _tuple;
};

class OutputQueue : public base::BlockingQueue<OutputItem*> {
};

}
}

#include "ideoengine/collector/OutputItem.tcc"

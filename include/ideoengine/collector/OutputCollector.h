

#pragma once

#include <memory>
#include <string>

namespace ideoengine {
namespace base {
class Tuple;
}

namespace collector {

class OutputQueue;

class OutputCollector {
public:
    OutputCollector();
    OutputCollector(int32_t taskIndex, const std::string& taskName, std::shared_ptr<OutputQueue> queue);

    void SetQueue(std::shared_ptr<OutputQueue> queue) {
        _queue = queue;
    }

    std::shared_ptr<OutputQueue> GetQueue() const {
        return _queue;
    }

    void Emit(const ideoengine::base::Tuple& tuple);

private:
    int32_t _taskIndex;
    std::string _taskName;
    std::shared_ptr<OutputQueue> _queue;
};

}
}

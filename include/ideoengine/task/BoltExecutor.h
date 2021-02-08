

#pragma once

#include "ideoengine/task/Executor.h"
#include <thread>
#include <memory>

namespace ideoengine {

namespace bolt {
class IBolt;
}

namespace collector {
class TaskQueue;
}

namespace task {

class BoltExecutor : public Executor {
public:
    BoltExecutor();
    ~BoltExecutor() {}

    void Start();

    std::shared_ptr<bolt::IBolt> GetBolt() {
        return _bolt;
    }

    void SetBolt(bolt::IBolt* bolt) {
        _bolt.reset(bolt);
    }

    void SetTaskQueue(std::shared_ptr<collector::TaskQueue> taskQueue) {
        _taskQueue = taskQueue;
    }

private:
    void StartLoop();

    std::thread _thread;
    std::shared_ptr<bolt::IBolt> _bolt;
    std::shared_ptr<collector::TaskQueue> _taskQueue;
};

}
}

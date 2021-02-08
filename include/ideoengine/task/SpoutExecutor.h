

#pragma once

#include "ideoengine/task/Executor.h"
#include <thread>
#include <memory>

namespace ideoengine {

namespace spout {
class ISpout;
}
namespace task {

class SpoutExecutor : public Executor {
public:
    SpoutExecutor();
    ~SpoutExecutor() {}

    void Start();

    void SetSpout(spout::ISpout* spout)
    {
        _spout.reset(spout);
    }

    std::shared_ptr<spout::ISpout> GetSpout() {
        return _spout;
    }

    int32_t GetFlowParam() const
    {
        return _flowParam;
    }

    void SetFlowParam(int32_t flowParam)
    {
        _flowParam = flowParam;
    }

private:
    void MainLoop();

    std::thread _thread;
    std::shared_ptr<spout::ISpout> _spout;
    int32_t _flowParam;
};

}
}

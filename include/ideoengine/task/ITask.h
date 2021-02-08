

#pragma once

#include "ideoengine/collector/OutputCollector.h"

#include <vector>
#include <memory>

namespace ideoengine {
namespace task {

class ITask {
public:
    virtual void Prepare(std::shared_ptr<ideoengine::collector::OutputCollector> outputCollector) = 0;
    virtual void Cleanup() = 0;
    virtual std::vector<std::string> DeclareFields() = 0;
};

}
}

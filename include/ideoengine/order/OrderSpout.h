

#pragma once

#include "ideoengine/spout/ISpout.h"

namespace ideoengine {
namespace order {

class OrderOutputCollector;

class OrderSpout : public ideoengine::spout::ISpout {
public:
    void Prepare(std::shared_ptr<collector::OutputCollector> outputCollector) override;
    virtual void Prepare(std::shared_ptr<OrderOutputCollector> outputCollector) = 0;
};

}
}

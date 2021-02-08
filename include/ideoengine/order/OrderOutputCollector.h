

#pragma once

#include "ideoengine/order/OrderTuple.h"

#include <memory>

namespace ideoengine {

namespace collector {
class OutputCollector;
}

namespace order {

class OrderOutputCollector {
public:
    OrderOutputCollector(std::shared_ptr<collector::OutputCollector> collector);
    void Emit(const OrderTuple& tuple);

private:
    std::shared_ptr<collector::OutputCollector> _collector;
};

}
}

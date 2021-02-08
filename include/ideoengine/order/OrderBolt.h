

#pragma once

#include "ideoengine/order/OrderTuple.h"
#include "ideoengine/bolt/IBolt.h"
#include <list>

namespace ideoengine {
namespace order {

class OrderOutputCollector;

class OrderBolt : public bolt::IBolt {
public:
    OrderBolt(bool isFinal);

    void Prepare(std::shared_ptr<collector::OutputCollector> outputCollector) override;
    void Execute(const base::Tuple& tuple) override;

    virtual void Prepare(std::shared_ptr<OrderOutputCollector> outputCollector) = 0;
    virtual void Execute(const OrderTuple& tuple) = 0;

    bool IsFinal() const {
        return _isFinal;
    }

    void SetFinal(bool isFinal) {
        _isFinal = isFinal;
    }

private:
    void InsertTuple(const OrderTuple& tuple);

private:
    bool _isFinal;
    int64_t _nextOrderId;
    std::list<OrderTuple> _tupleQueue;
};

}
}

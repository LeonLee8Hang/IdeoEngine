#include "ideoengine/order/OrderBolt.h"
#include "ideoengine/order/OrderOutputCollector.h"
#include <algorithm>

namespace ideoengine {
namespace order {

OrderBolt::OrderBolt(bool isFinal) : _isFinal(isFinal), _nextOrderId(1) {
}

void OrderBolt::Prepare(std::shared_ptr<collector::OutputCollector> outputCollector)
{
    std::shared_ptr<ideoengine::order::OrderOutputCollector> orderCollector =
            std::make_shared<ideoengine::order::OrderOutputCollector>(outputCollector);

    Prepare(orderCollector);
    _nextOrderId = 1;
    _tupleQueue.clear();
}

void OrderBolt::Execute(const base::Tuple& tuple)
{
    OrderTuple orderTuple = tuple;
    orderTuple.ParseBaseTuple();

    if ( orderTuple.GetOrderId() != _nextOrderId ) {
        InsertTuple(orderTuple);

        return;
    }

    while ( true ) {
        base::Tuple baseTuple = orderTuple.ToBaseTuple();
        Execute(baseTuple);
        _nextOrderId ++;

        orderTuple = _tupleQueue.front();
        if ( orderTuple.GetOrderId() != _nextOrderId ) {
            break;
        }

        _tupleQueue.pop_front();
    }
}

void OrderBolt::InsertTuple(const OrderTuple& tuple)
{
    auto insertPos = std::find_if(_tupleQueue.begin(), _tupleQueue.end(),
                               [tuple](const OrderTuple& another) -> bool {
        return another.GetOrderId() > tuple.GetOrderId();
    });

    if ( insertPos == _tupleQueue.end() ) {
        _tupleQueue.push_back(tuple);

        return;
    }

    _tupleQueue.insert(insertPos, tuple);
}

}

}

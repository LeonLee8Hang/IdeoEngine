#include "ideoengine/order/OrderTuple.h"

namespace ideoengine {
namespace order {

OrderTuple::OrderTuple(const base::Tuple& tuple) : base::Tuple(tuple), _orderId(0) {
}

base::Tuple OrderTuple::ToBaseTuple() const
{
    base::Tuple tuple = *this;
    tuple.Add({ _orderId });

    return tuple;
}

void OrderTuple::ParseBaseTuple()
{
    _orderId = GetValues()[GetSize() - 1].GetInt64Value();
    Pop();
}

}
}



#pragma once

#include "ideoengine/base/Values.h"

namespace ideoengine {
namespace order {

class OrderTuple : public ideoengine::base::Tuple {
public:
    OrderTuple() = default;
    OrderTuple(const base::Tuple& tuple);

    base::Value& operator[](size_t index) {
        return base::Tuple::operator [](index);
    }

    const base::Value& operator[](size_t index) const {
        return base::Tuple::operator [](index);
    }

    base::Value& operator[](const std::string& fieldName) {
        return base::Tuple::operator [](fieldName);
    }

    const base::Value& operator[](const std::string& fieldName) const {
        return base::Tuple::operator [](fieldName);
    }

    base::Tuple ToBaseTuple() const;
    void ParseBaseTuple();

    int64_t GetOrderId() const {
        return _orderId;
    }

    void SetOrderId(int64_t orderId) {
        _orderId = orderId;
    }

private:
    int64_t _orderId;
};

}
}

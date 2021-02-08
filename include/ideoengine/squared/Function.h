

#pragma once

#include "Operation.h"

namespace ideoengine {
    namespace squared {
        class Function : public Operation {
            virtual void Execute(const SquaredTuple& tuple,
                SquaredCollector* collector) = 0;
        };
    }
}
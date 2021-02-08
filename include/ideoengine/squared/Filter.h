

#pragma once

#include "Operation.h"
#include "SquaredCollector.h"
#include "SquaredTuple.h"

namespace ideoengine {
    namespace squared {
        class Function : public Operation {
            virtual void Execute(const SquaredTuple& tuple,
                SquaredCollector* collector) override {
                if ( Filter(tuple) ) {
                    collector->Emit(tuple.GetValues())
                }
            }

            virtual bool Filter(const SquaredTuple& tuple) = 0;
        };
    }
}

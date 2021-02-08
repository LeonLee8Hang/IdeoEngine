

#pragma once

#include "SquaredBolt.h"

namespace ideoengine {
    namespace squared {
        class Operation;

        class EachBolt : public SquaredBolt {
        public:
            EachBolt(const base::Fields& inputFields,
                Operation* operation, const base::Fields& outputFields);

            virtual void Execute(const SquaredTuple& tuple,
                SquaredCollector* collector) override;

        private:
            Operation* _operation;
        };
    }
}
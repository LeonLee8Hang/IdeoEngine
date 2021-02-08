

#pragma once

#include "Operation.h"
#include <set>

namespace ideoengine {
    namespace squared {
        class BaseAggregator : public Operation {
        public:
            virtual void Execute(const SquaredTuple& tuple,
                SquaredCollector* collector);

            virtual void Init(int32_t batchId, SquaredCollector* collector) = 0;
            virtual void Aggregate(const SquaredTuple& tuple, SquaredCollector* collector) = 0;
            virtual void Complete(SquaredCollector* collector) = 0;

        private:
            std::set<int32_t> _batches;
        };
    }
}

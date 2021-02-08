

#pragma once

#include "Operation.h"
#include <set>

namespace ideoengine {
    namespace trident {
        class BaseAggregater : public Operation {
        public:
            virtual void Execute(const TridentTuple& tuple,
                TridentCollector* collector);

            virtual void Init(int32_t batchId, TridentCollector* collector) = 0;
            virtual void Aggregate(const TridentTuple& tuple, TridentCollector* collector) = 0;
            virtual void Complete(TridentCollector* collector) = 0;

        private:
            std::set<int32_t> _batches;
        };
    }
}

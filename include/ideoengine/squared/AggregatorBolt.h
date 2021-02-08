

#pragma once

#include "SquaredBolt.h"

namespace ideoengine {
    namespace squared {
        class BaseAggregator;

        class AggregatorBolt : public SquaredBolt {
        public:
            AggregatorBolt(BaseAggregator* aggregator, 
                const base::Fields& outputFields);

            virtual void Execute(const SquaredTuple& tuple,
                SquaredCollector* collector) override;

        private:
            BaseAggregator* _aggregator;
        };
    }
}
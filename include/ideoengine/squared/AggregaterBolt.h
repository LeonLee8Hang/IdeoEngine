

#pragma once

#include "TridentBolt.h"

namespace ideoengine {
    namespace trident {
        class BaseAggregater;

        class AggregaterBolt : public TridentBolt {
        public:
            AggregaterBolt(BaseAggregater* aggregater, 
                const base::Fields& outputFields);

            virtual void Execute(const TridentTuple& tuple,
                TridentCollector* collector) override;

        private:
            BaseAggregater* _aggregater;
        };
    }
}
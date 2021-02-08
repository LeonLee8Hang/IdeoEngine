

#pragma once

#include "AggregatorBolt.h"
#include <memory>

namespace ideoengine {
    namespace base {
        class Fields;
    }

    namespace squared {
        class SquaredStateFactory;
        class BaseAggregator;
        class SquaredState;

        class PersistAggregatorBolt : public AggregatorBolt {
        public:
            PersistAggregatorBolt(const SquaredStateFactory * factory,
                BaseAggregator* aggregator,
                const base::Fields& outputFields);

            SquaredState* GetState() {
                return _state;
            }

        private:
            std::shared_ptr<SquaredState> _state;
        };
    }
}
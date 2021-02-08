

#include "AggregatorBolt.h"
#include "Aggregator.h"

namespace ideoengine {
    namespace squared {
        AggregatorBolt::AggregatorBolt(
            BaseAggregator * aggregator, const base::Fields & outputFields) :
            SquaredBolt({}, outputFields), _aggregator(aggregator)
        {
        }

        void AggregatorBolt::Execute(const SquaredTuple & tuple, SquaredCollector * collector)
        {
            _aggregator->Execute(tuple, collector);
        }
    }
}
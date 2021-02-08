

#include "AggregaterBolt.h"
#include "Aggregater.h"

namespace ideoengine {
    namespace trident {
        AggregaterBolt::AggregaterBolt(
            BaseAggregater * aggregater, const base::Fields & outputFields) :
            TridentBolt({}, outputFields), _aggregater(aggregater)
        {
        }

        void AggregaterBolt::Execute(const TridentTuple & tuple, TridentCollector * collector)
        {
            _aggregater->Execute(tuple, collector);
        }
    }
}


#include "PersistentAggregatorBolt.h"
#include "SquaredStateFactory.h"
#include "SquaredState.h"
#include "BaseAggregator.h"
#include "ideoengine/base/Fields.h"

namespace ideoengine {
    namespace squared {
        PersistAggregatorBolt::PersistAggregatorBolt(
            const SquaredStateFactory * factory, 
            BaseAggregator * aggregator, const base::Fields & outputFields)
        {
            _state = std::shared_ptr<SquaredState>(factory->CreateState());
        }
    }
}

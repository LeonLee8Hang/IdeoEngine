

#include "PersistentAggregaterBolt.h"
#include "TridentStateFactory.h"
#include "TridentState.h"
#include "BaseAggregater.h"
#include "ideoengine/base/Fields.h"

namespace ideoengine {
    namespace trident {
        PersistAggregaterBolt::PersistAggregaterBolt(
            const TridentStateFactory * factory, 
            BaseAggregater * aggregater, const base::Fields & outputFields)
        {
            _state = std::shared_ptr<TridentState>(factory->CreateState());
        }
    }
}

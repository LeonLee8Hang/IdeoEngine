

#include "GroupByBolt.h"
#include "SquaredCollector.h"
#include "SquaredTuple.h"

namespace ideoengine {
    namespace squared {
        GroupByBolt::GroupByBolt(const base::Fields & fields) :
            SquaredBolt(Fields(), fields)
        {
        }

        void GroupByBolt::Execute(const SquaredTuple & tuple, SquaredCollector * collector)
        {
            collector->Emit(tuple.GetValues());
        }
    }
}



#include "EachBolt.h"
#include "Operation.h"

namespace ideoengine {
    namespace squared {
        EachBolt::EachBolt(const base::Fields & inputFields, 
            Operation * operation, const base::Fields & outputFields) :
                SquaredBolt(inputFields, outputFields),
                _operation(operation)
        {
        }

        void EachBolt::Execute(const SquaredTuple & tuple, 
            SquaredCollector * collector)
        {
            _operation->Execute(tuple, collector);
        }
    }
}

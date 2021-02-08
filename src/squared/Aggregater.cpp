

#include "Aggregater.h"
#include "TridentTuple.h"
#include "TridentCollector.h"

namespace ideoengine {
    namespace trident {
        void BaseAggregater::Execute(const TridentTuple & tuple, TridentCollector * collector)
        {
            int32_t batchId = tuple.GetBatchId();
            collector->SetBatchId(batchId);

            if ( _batches.find(batchId) == _batches.end ) {
                _batches.insert(batchId);
                this->Init(batchId, collector);
            }
            else if ( collector->IsFinished() ) {
                this->Complete(collector);
            }
            else {
                this->Aggregate(tuple, collector);
            }
        }
    }
}
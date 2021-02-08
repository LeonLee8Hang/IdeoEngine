

#include "Aggregator.h"
#include "SquaredTuple.h"
#include "SquaredCollector.h"

namespace ideoengine {
    namespace squared {
        void BaseAggregator::Execute(const SquaredTuple & tuple, SquaredCollector * collector)
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
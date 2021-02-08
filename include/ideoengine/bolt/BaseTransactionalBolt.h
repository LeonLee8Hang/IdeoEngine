#pragma once

#include "BaseBatchBolt.h"
#include "TransactionAttempt.h"

namespace ideoengine {
    namespace base {
        class BatchOutputCollector;
    }

    namespace bolt {
        class BaseTransactionalBolt : public BaseBatchBolt {
        public:
            virtual void Prepare(base::BatchOutputCollector& collector, TransactionAttempt* attempt) = 0;
            void Prepare(base::BatchOutputCollector& collector, void* id) {
            }
        };
    }
}

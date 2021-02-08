

#pragma once

#include "ideoengine/base/OutputCollector.h"

namespace ideoengine {
    namespace squared {
        class SquaredCollector : public base::OutputCollector {
        public:
            bool IsFinished();

            void SetBatchId(int32_t batchId) {
                _batchId = batchId;
            }

            int32_t GetBatchId() const {
                return _batchId;
            }

        private:
            int32_t batchId;
        };
    }
}
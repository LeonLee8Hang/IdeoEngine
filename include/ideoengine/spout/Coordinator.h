

#pragma once

#include "ideoengine/spout/ISpout.h"

namespace ideoengine {
    namespace spout {
        class Coordinator : public ISpout {
        public:
            virtual void Open(base::OutputCollector& outputCollector) {
                _outputCollector = &outputCollector;
            }

            virtual void Close() {

            }
            virtual void Execute() {

            }

        private:
            base::OutputCollector* _outputCollector;
        };
    }
}
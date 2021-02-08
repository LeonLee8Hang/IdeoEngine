

#pragma once

#include "ideoengine/spout/ISpout.h"

namespace ideoengine {
    namespace squared {
        class SquaredSpout : public ISpout {
        public:
            SquaredSpout() {}

            virtual void Open(base::OutputCollector& outputCollector) = 0;
            virtual void Close() = 0;
            virtual void Execute() = 0;

            virtual ISpout* Clone() const = 0;
        };
    }
}
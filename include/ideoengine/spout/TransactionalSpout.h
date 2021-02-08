

#pragma once

#include "Coordinator.h"
#include "Emitter.h"

namespace ideoengine {
    namespace spout {
        class TransactionalSpout {
        public:
            virtual ideoengine::spout::Coordinator* GetCoordinator() = 0;
            virtual ideoengine::bolt::Emitter* GetEmitter() = 0;
        };
    }
}

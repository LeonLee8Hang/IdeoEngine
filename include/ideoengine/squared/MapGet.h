

#pragma once

#include "SquaredBolt.h"
#include "SquaredState.h"
#include "SquaredTuple.h"

namespace ideoengine {
    namespace squared {
        class MapGet : public SquaredBolt {
        public:
            MapGet() 
            {
            }

            void SetState(SquaredState* state) {
                _state = state;
            }

            virtual void Execute(const SquaredTuple& tuple,
                SquaredCollector* collector) override {
                base::Value key = tuple.GetValues()[0];
                base::Value value = _state->Get(key);
                collector->Emit(Values(value));
            }
        
        private:
            SquaredState* _state;
        };
    }
}
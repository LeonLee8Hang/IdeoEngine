

#pragma once

namespace ideoengine {
    namespace squared {
        class SquaredTuple;
        class SquaredCollector;

        class Operation {
        public:
            virtual void Execute(const SquaredTuple& tuple,
                SquaredCollector* collector) = 0;
        };
    }
}
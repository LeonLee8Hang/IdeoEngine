

#pragma once

#include "SquaredBolt.h"

namespace ideoengine {
    namespace squared {
        class GroupByBolt : public SquaredBolt {
        public:
            GroupByBolt(const base::Fields& fields);

            virtual void Execute(const SquaredTuple& tuple,
                SquaredCollector* collector) override;
        };

    }
}
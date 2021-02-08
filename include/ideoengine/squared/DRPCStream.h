

#pragma once

#include "ideoengine/base/Fields.h"

namespace ideoengine {
    namespace squared {
        class SquaredTopology;
        class SquaredSpout;
        class Operation;
        class BaseFunction;
        class BaseFilter;
        class BaseAggregator;
        class SquaredState;
        class SquaredStateFactory;
        class MapGet;

        class DRPCStream {
        public:
            DRPCStream();
            DRPCStream(const std::string& spoutName.
                SquaredSpout* spout);

            DRPCStream* Each(const base::Fields& inputFields,
                Operation* operation, const base::Fields& outputFields);
            DRPCStream* GroupBy(const Fields& fields);
            DRPCStream* StateQuery(SquaredState* state, base::Fields& inputFields,
                MapGet* mapGetter, base::Fields& outputFields);
            DRPCStream* Aggregate(base::Fields& inputFields, BaseAggregator* aggregator,
                base::Fields* outputFields);
            std::string WaitFormResult(const std::string& args);

            void Deploy(SquaredToplogy* topology);
        };
    }
}
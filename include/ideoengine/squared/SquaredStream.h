

#pragma once

#include "ideoengine/base/Fields.h"
#include <list>
#include <memory>

namespace ideoengine {
    namespace bolt {
        class IBolt;
    }

    namespace squared {
        class SquaredToplogy;
        class SquaredSpout;
        class Operation;
        class BaseFunction;
        class BaseFilter;
        class BaseAggregator;
        class SquaredState;
        class SquaredStateFactory;

        class SquaredStream {
        public:
            SquaredStream();
            SquaredStream(const std::string& spoutName,
                SquaredSpout* spout);

            SquaredStream* Each(const base::Fields& inputFields,
                Operation* operation, const base::Fields& outputFields);
            SquaredStream* GroupBy(const base::Fields& fields);
            SquaredState* PersistentAggregate(const SquaredStateFactory* factory,
                BaseAggregator* operation, const base::Fields& fields);

            void Deploy(SquaredToplogy* topology);

        private:
            std::string _spoutName;
            std::shared_ptr<SquaredSpout> _spout;
            std::list<std::shared_ptr<bolt::IBolt>> _bolts;
            std::list<std::string> _boltNames;
        };
    }
}
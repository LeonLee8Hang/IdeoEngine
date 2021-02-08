

#pragma once

#include "ideoengine/base/Fields.h"
#include "ideoengine/bolt/IBolt.h"

namespace ideoengine {
    namespace squared {
        class Operation;
        class SquaredTuple;
        class SquaredCollector;

        class SquaredBolt : public IBolt {
        public:
            SquaredBolt(const base::Fields& inputFields,
                const base::Fields& outputFields);

            virtual void Prepare(base::OutputCollector& outputCollector) override;
            virtual void Cleanup() override;
            virtual void Execute(const base::Values& values) override;
            virtual void Execute(const SquaredTuple& tuple,
                SquaredCollector* collector) = 0;

            virtual IBolt* Clone() const override;

            virtual Fields DeclareFields() const override;

        private:
            base::Fields _inputFields;
            base::Fields _outputFields;
            SquaredCollector* _collector;
        };
    }
}


#include "SquaredBolt.h"
#include "SquaredTuple.h"

namespace ideoengine {
    namespace squared {
        SquaredBolt::SquaredBolt(const base::Fields & inputFields,
            const base::Fields & outputFields) :
                _inputFields(inputFields),
                _outputFields(outputFields)
        {
        }

        void SquaredBolt::Prepare(base::OutputCollector & outputCollector)
        {
            this->_collector = &outputCollector;
        }

        void SquaredBolt::Cleanup()
        {
        }

        void SquaredBolt::Execute(const base::Values & values)
        {
            Execute(SquaredTuple(_inputFields, values), _collector)
        }

        IBolt* SquaredBolt::Clone() const
        {
            return new SquaredBolt(this);
        }
        
        Fields SquaredBolt::DeclareFields() const
        {
            return _outputFields;
        }
    }
}
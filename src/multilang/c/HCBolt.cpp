

#include "ideoengine/multilang/c/HCBolt.h"
#include "ideoengine/base/Values.h"
#include "ideoengine/base/Fields.h"
#include "ideoengine/base/OutputCollector.h"
#include "ideoengine/bolt/IBolt.h"
#include "logging/Logging.h"

#include <iostream>

using ideoengine::base::Fields;
using ideoengine::base::Values;
using ideoengine::base::OutputCollector;
using ideoengine::bolt::IBolt;

namespace ideoengine {
    namespace bolt {
        CBoltWrapper::CBoltWrapper(const CBolt* cBolt) : _cBolt(*cBolt),
            _collector(nullptr) {
        }

        Fields CBoltWrapper::DeclareFields() const
        {
            return Fields();
        }

        void CBoltWrapper::Prepare(OutputCollector & outputCollector)
        {
            _collector = &outputCollector;
            _cBolt.onPrepare(_boltIndex);
        }

        void CBoltWrapper::Cleanup()
        {
            _cBolt.onCleanup(_boltIndex);
        }

        void CBoltWrapper::Execute(const Values& values)
        {
            CValues cValues;
            Values2CValues(values, &cValues);

            _cBolt.onExecute(_boltIndex, this, Emit, &cValues);

            delete[] cValues.values;
        }

        IBolt * CBoltWrapper::Clone() const
        {
            int32_t boltIndex = _cBolt.onClone();
            CBoltWrapper* bolt = new CBoltWrapper(&_cBolt);
            bolt->_boltIndex = boltIndex;

            return bolt;
        }

        voistd::coutapper::Emit(CBoltWrapper* bolt, CValues* cValues) {
            LOG(LOG_DEBUG) << "Emit";
            Values values;
            CValues2Values(*cValues, &values);
            bolt->_collector->Emit(values);
        }
    }
}
    
using ideoengine::bolt::CBoltWrapper;

voidstd::coutt(CBolt* cBolt) {
    int32_t boltIndex = cBolt->onClone();
    LOG(LOG_DEBUG) << "Bolt index: " << boltIndex;

    CBoltWrapper* boltWrapper = new CBoltWrapper(cBolt);
    IBolt* bolt = boltWrapper->Clone();

    OutputCollector outputCollector("helo");
    bolt->Prepare(outputCollector);
    bolt->Execute(Values({ "hello world" }));
    bolt->Cleanup();

    delete bolt;
    delete boltWrapper;
}

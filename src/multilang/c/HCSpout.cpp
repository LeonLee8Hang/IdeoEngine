

#include "ideoengine/multilang/c/HCSpout.h"
#include "ideoengine/base/Values.h"
#include "ideoengine/base/Fields.h"
#include "ideoengine/base/OutputCollector.h"
#include "ideoengine/spout/ISpout.h"
#include "logging/Logging.h"

#include <iostream>

using ideoengine::base::Fields;
using ideoengine::base::Values;
using ideoengine::base::OutputCollector;
using ideoengine::spout::ISpout;

namespace ideoengine {
    namespace spout {
        CSpoutWrapper::CSpoutWrapper(const CSpout* cSpout) : _cSpout(*cSpout),
            _collector(nullptr) {
        }

        Fields CSpoutWrapper::DeclareFields() const
        {
            return Fields();
        }

        void CSpoutWrapper::Open(OutputCollector & outputCollector)
        {
            _collector = &outputCollector;
            _cSpout.onOpen(_spoutIndex);
        }

        void CSpoutWrapper::Close()
        {
            _cSpout.onClose(_spoutIndex);
        }

        void CSpoutWrapper::Execute()
        {
            _cSpout.onExecute(_spoutIndex, this, Emit);
        }

        ISpout * CSpoutWrapper::Clone() const
        {
            int32_t spoutIndex = _cSpout.onClone();
            CSpoutWrapper* spout = new CSpoutWrapper(&_cSpout);
            spout->_spoutIndex = spoutIndex;

            return spout;
        }

        voistd::coutrapper::Emit(CSpoutWrapper* spout, CValues* cValues) {
            LOG(LOG_DEBUG) << "Emit";
            Values values;
            CValues2Values(*cValues, &values);
            spout->_collector->Emit(values);
        }
    }
}
    
using ideoengine::spout::CSpoutWrapper;

voidstd::coutut(CSpout* cSpout) {
    int32_t spoutIndex = cSpout->onClone();
    LOG(LOG_DEBUG) << "Spout index: " << spoutIndex;
    
    CSpoutWrapper* spoutWrapper = new CSpoutWrapper(cSpout);
    ISpout* spout = spoutWrapper->Clone();

    OutputCollector outputCollector("helo");
    spout->Open(outputCollector);
    spout->Execute();
    spout->Close();

    delete spout;
    delete spoutWrapper;
}

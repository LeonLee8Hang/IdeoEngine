

#pragma once

#include "ideoengine/multilang/common/Common.h"
#include "ideoengine/multilang/c/HCValues.h"

BEGIN_C_DECALRE

#include <stdint.h>

typedef int32_t (*CSpoutClone)();
typedef int32_t(*CSpoutOpen)(int32_t spoutIndex);
typedef int32_t(*CSpoutClose)(int32_t spoutIndex);
typedef int32_t(*CSpoutExecute)(int32_t spoutIndex, void* wrapper, void* emitter);

typedef struct {
    CSpoutClone onClone;
    CSpoutOpen onOpen;
    CSpoutClose onClose;
    CSpoutExecute onExecute;
} CSpout;

void TestCSpout(CSpout* cSpout);

END_C_DECLARE

#ifdef __cplusplus

#include "ideoengine/base/Values.h"
#include "ideoengine/base/Fields.h"
#include "ideoengine/spout/ISpout.h"

namespace ideoengine {
    namespace base {
        class OutputCollector;
    }

    namespace spout {
        class CSpoutWrapper : public ISpout {
        public:
            CSpoutWrapper(const CSpout* cSpout);
            virtual base::Fields DeclareFields() const override;
            virtual void Open(base::OutputCollector & outputCollector) override;
            virtual void Close() override;
            virtual void Execute() override;
            virtual ISpout * Clone() const override;
            static void Emit(CSpoutWrapper* spout, CValues* cValues);

        private:
            CSpout _cSpout;
            int32_t _spoutIndex;
            base::OutputCollector* _collector;
        };
    }
}

#endif

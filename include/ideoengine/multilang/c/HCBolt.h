#pragma once

#include "ideoengine/multilang/common/Common.h"
#include "ideoengine/multilang/c/HCValues.h"

BEGIN_C_DECALRE

#include <stdint.h>

typedef int32_t(*CBoltClone)();
typedef int32_t(*CBoltPrepare)(int32_t boltIndex);
typedef int32_t(*CBoltCleanup)(int32_t boltIndex);
typedef int32_t(*CBoltExecute)(int32_t boltIndex,
    void* wrapper, void* emitter, CValues* cValues);

typedef struct {
    CBoltClone onClone;
    CBoltPrepare onPrepare;
    CBoltCleanup onCleanup;
    CBoltExecute onExecute;
} CBolt;

void TestCBolt(CBolt* cBolt);

END_C_DECLARE

#ifdef __cplusplus

#include "ideoengine/base/Values.h"
#include "ideoengine/base/Fields.h"
#include "ideoengine/bolt/IBolt.h"

namespace ideoengine {
    namespace base {
        class OutputCollector;
    }

    namespace bolt {
        class CBoltWrapper : public IBolt {
        public:
            CBoltWrapper(const CBolt* cBolt);
            virtual base::Fields DeclareFields() const;
            virtual void Prepare(base::OutputCollector & outputCollector);
            virtual void Cleanup() override;
            virtual void Execute(const base::Values& values);
            virtual bolt::IBolt * Clone() const override;

            static void Emit(CBoltWrapper* bolt, CValues* cValues);

        private:
            CBolt _cBolt;
            int32_t _boltIndex;
            base::OutputCollector* _collector;
        };
    }
}

#endif

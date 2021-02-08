

#pragma

#include "ideoengine/multilang/common/Common.h"
#include "HCBolt.h"
#include "HCSpout.h"

BEGIN_C_DECALRE

typedef struct {
    CBolt* cBolts;
    char** boltNames;
    char** boltSources;
    int32_t boltCount;

    CSpout* cSpouts;
    char** spoutNames;
    int32_t spoutCount;
} CTopology;

void StartTopology(CTopology* cTopology);

END_C_DECLARE
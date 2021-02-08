

#pragma once

#include "ideoengine/multilang/common/Common.h"

#include <stdint.h>

#define HC_TYPE_BOOLEAN 0
#define HC_TYPE_CHARACTER 1
#define HC_TYPE_INT8 2
#define HC_TYPE_INT16 3
#define HC_TYPE_INT32 4
#define HC_TYPE_INT64 5
#define HC_TYPE_FLOAT 6
#define HC_TYPE_DOUBLE 7
#define HC_TYPE_STRING 8

BEGIN_C_DECALRE

typedef struct {
    int8_t type;
    union {
        int8_t booleanValue;
        char characterValue;
        int8_t int8Value;
        int16_t int16Value;
        int32_t int32Value;
        int64_t int64Value;
        float floatValue;
        double doubleValue;
        char* stringValue;
    };
    int32_t length;
} CValue;

typedef struct {
    int32_t length;
    CValue* values;
} CValues;

void PrintCValues(CValues* values);

#ifdef __cplusplus

namespace ideoengine {
    namespace base {
        class Values;
    }
};

void Values2CValues(const ideoengine::base::Values& values, CValues* cValues);
void CValues2Values(const CValues& cValues, ideoengine::base::Values* values);

#endif

END_C_DECLARE


#pragma once

#include "ideoengine/base/Values.h"

namespace ideoengine {
    namespace squared {
        class SquaredState {
            virtual void Init() = 0;
            virtual void Set(const base::Value& key, const base::Value& value) = 0;
            virtual const base::Value& value Get(const base::Value& key) = 0;
            virtual void Destroy() = 0;
        };
    }
}
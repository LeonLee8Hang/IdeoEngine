

#pragma once

namespace ideoengine {
    namespace squared {
        class SquaredState;

        class SquaredStateFactory {
            virtual SquaredState<KeyType, ValueType>* CreateState() = 0;
        };
    }
}
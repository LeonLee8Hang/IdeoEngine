

#pragma once

#include "ideoengine/multilang/java/SignatureImpl.h"

namespace ideoengine {
namespace java {

class Object {
public:
    static std::string GetTypeSignature(const std::string& typeName) {
        return "L" + typeName + ";";
    }
};

}
}

#define ideoengine_JAVA_REGISTER_CLASS(CppType, JavaType) \
namespace ideoengine { \
namespace java { \
\
namespace signature_impl { \
\
template <> \
inline std::string ForType(const CppType*) { \
    return Object::GetTypeSignature(JavaType); \
} \
\
} \
\
} \
}

ideoengine_JAVA_REGISTER_CLASS(ideoengine::java::Object, "java/lang/Object")



#pragma once

#include <jni.h>

#include <string>
#include <exception>
#include <typeinfo>
#include <cstdint>
#include <iostream>

namespace ideoengine {
namespace java {

#define HJARG(Type) (const Type*)(nullptr)

class Signature {
public:
    static const char ArgumentLeftBrace = '(';
    static const char ArgumentRightBrace = ')';

    template <class Type>
    static std::string ForType(const Type* t) {
        return signature_impl::ForType(t);
    }

    static std::string ForMethodArgs() {
        return "";
    }

    template <class Arg, class ...Args>
    static std::string ForMethodArgs(const Arg*, Args ...args) {
        return ForType<Arg>((const Arg*)(nullptr)) + ForMethodArgs(args...);
    }

    template <class ReturnValue, class ...Args>
    static std::string ForMethod(const Args* ...args) {
        return "(" + ForMethodArgs(args...) + ")" + ForType<ReturnValue>((const ReturnValue*)(nullptr));
    }
};

}
}

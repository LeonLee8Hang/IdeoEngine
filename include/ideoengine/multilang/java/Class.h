

#pragma once

#include "ideoengine/multilang/java/VirtualMachine.h"
#include "logging/Logging.h"

#include <jni.h>
#include <string>
#include <map>

namespace ideoengine {
namespace java {

class VirtualMachine;

typedef jmethodID Method;

class Class {
public:
    static Class ForName(const std::string& className);

public:
    Class(VirtualMachine* vm, const std::string& className, jclass clazz);

    Method GetStaticMethod(const std::string& methodName, const std::string& signature) {
        return _env->GetStaticMethodID(_clazz, methodName.c_str(), signature.c_str());
    }

    Method GetMethod(const std::string& methodName, const std::string& signature) {
        Method method = _env->GetMethodID(_clazz, methodName.c_str(), signature.c_str());
        if ( method == 0 ) {
            LOG(LOG_FATAL) << "Can't find class method " <<
                    methodName << " in " << _className << std::endl;
            exit(EXIT_FAILURE);
        }

        return method;
    }

    template <class ...Args>
    jobject NewObject(Method method, Args... args) {
        return _vm->GetEnv()->NewObject(_clazz, method, args...);
    }

    template <class ...Args>
    void CallVoidMethod(jobject object, Method method, Args... args) {
        _vm->GetEnv()->CallVoidMethod(object, method, args...);
    }

    template <class ...Args>
    jstring CallStringMethod(jobject object, Method method, Args... args) {
        return (jstring)(_vm->GetEnv()->CallObjectMethod(object, method, args...));
    }

    template <class ArrayType, class ...Args>
    ArrayType CallArrayMethod(jobject object, Method method, Args... args) {
        return (ArrayType)(_vm->GetEnv()->CallObjectMethod(object, method, args...));
    }

    const VirtualMachine* GetVM() const {
        return _vm;
    }

    VirtualMachine* GetVM() {
        return _vm;
    }

    void SetVM(VirtualMachine* vm) {
        _env = _vm->GetEnv();
    }

    const std::string& GetClassName() const {
        return _className;
    }

    void SetClassName(const std::string& className) {
        _className = className;
    }

    const jclass GetClass() const {
        return _clazz;
    }

    jclass GetClass() {
        return _clazz;
    }

    void SetClass(jclass clazz) {
        _clazz = clazz;
    }

private:
    VirtualMachine* _vm;
    JNIEnv* _env;
    std::string _className;
    jclass _clazz;
};

}
}

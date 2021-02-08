

#pragma once

namespace ideoengine {
namespace java {

template <class CppClass, class... Args>
void NativeObjectWrapper::CreateObject(Args... args) {
    CppClass* calleeObject = new CppClass(args...);
    jlong calleeHandle = reinterpret_cast<int64_t>(calleeObject);

    jclass cls = _env->GetObjectClass(_object);
    jfieldID nativeHandleFieldId = _env->GetFieldID(cls, "nativeHandle", "J");
    if ( !nativeHandleFieldId ) {
        LOG(LOG_FATAL) << "Can't find field nativeHandle in class " << GetClassName() << std::endl;
    }

    _env->SetLongField(_object, nativeHandleFieldId, calleeHandle);
}

template <class CppClass>
void NativeObjectWrapper::DestroyObject() {
    jclass cls = _env->GetObjectClass(_object);
    jfieldID nativeHandleFieldId = _env->GetFieldID(cls, "nativeHandle", "J");
    if ( !nativeHandleFieldId ) {
        LOG(LOG_FATAL) << "Can't find field nativeHandle in class " << GetClassName() << std::endl;
    }

    jlong calleeHandle = _env->GetLongField(_object, nativeHandleFieldId);
    CppClass* calleeObject = reinterpret_cast<CppClass*>(calleeHandle);

    if ( calleeObject ) {
        delete calleeObject;
        calleeHandle = 0;
        _env->SetLongField(_object, nativeHandleFieldId, calleeHandle);
    }
}

template <class CppClass, class ResultType, class Method, class... Args>
ResultType NativeObjectWrapper::CallMethod(Method methodPointer, Args... args) {
    jclass cls = _env->GetObjectClass(_object);
    jfieldID nativeHandleFieldId = _env->GetFieldID(cls, "nativeHandle", "J");
    if ( !nativeHandleFieldId ) {
        LOG(LOG_FATAL) << "Can't find field nativeHandle in class " << GetClassName() << std::endl;
    }

    jlong calleeHandle = _env->GetLongField(_object, nativeHandleFieldId);
    CppClass* calleeObject = reinterpret_cast<CppClass*>(calleeHandle);

    return FromNative((calleeObject->*methodPointer)(args...));
}

template <class CppClass, class Method, class... Args>
void NativeObjectWrapper::CallVoidMethod(Method methodPointer, Args... args) {
    jclass cls = _env->GetObjectClass(_object);
    jfieldID nativeHandleFieldId = _env->GetFieldID(cls, "nativeHandle", "J");
    if ( !nativeHandleFieldId ) {
        LOG(LOG_FATAL) << "Can't find field nativeHandle in class " << GetClassName() << std::endl;
    }

    jlong calleeHandle = _env->GetLongField(_object, nativeHandleFieldId);
    CppClass* calleeObject = reinterpret_cast<CppClass*>(calleeHandle);

    (calleeObject->*methodPointer)(args...);
}

}
}

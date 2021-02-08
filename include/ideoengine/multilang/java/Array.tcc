

#pragma once

namespace ideoengine {
namespace java {

template <class Element>
Array<Element>::Array(jobjectArray array) : _vm(VirtualMachine::GetDefault()), _array(array) {
    JNIEnv* env = _vm->GetEnv();

    jsize arraySize = env->GetArrayLength(_array);
    _data.resize(arraySize);

    for ( int i = 0; i != arraySize; ++ i ) {
        _data[i] = Element(env->GetObjectArrayElement(array, i));
    }
}

template <class Element>
Array<Element>::Array(jobject array) : Array(jobjectArray(array)) {}

template <class Element>
Array<Element>::Array(size_t size) : _vm(VirtualMachine::GetDefault()), _data(size) {}

namespace signature_impl {

template <class Element>
std::string ForType(const Array<Element>*) {
    return "[" + ForType((const Element*)(nullptr));
}

}

}
}

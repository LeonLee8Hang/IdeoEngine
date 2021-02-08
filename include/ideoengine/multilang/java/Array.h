

#pragma once

#include "ideoengine/multilang/java/Class.h"
#include "ideoengine/multilang/java/Object.h"
#include "ideoengine/multilang/java/VirtualMachine.h"
#include "ideoengine/multilang/java/SignatureImpl.h"

#include <jni.h>
#include <vector>

namespace ideoengine {
namespace java {

template <class Element>
class Array : public Object {
public:
    Array(jobjectArray array);
    Array(jobject array);
    Array(size_t size);

    Element& operator[](int index) {
        return _data[index];
    }

    const Element& operator[](int index) const {
        return _data[index];
    }

    size_t GetSize() const {
        return _data.size();
    }

    const std::vector<Element>& GetData() const {
        return _data;
    }

private:
    VirtualMachine* _vm;
    jobjectArray _array;
    std::vector<Element> _data;
};

namespace signature_impl {

template <class Element>
std::string ForType(const Array<Element>*);

}
}
}

#include "ideoengine/multilang/java/Array.tcc"

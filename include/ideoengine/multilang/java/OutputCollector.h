

#pragma once

#include "ideoengine/multilang/java/String.h"
#include "ideoengine/multilang/java/Array.h"
#include "ideoengine/multilang/java/Class.h"

#include <jni.h>
#include <string>

namespace ideoengine {
namespace bolt {

class JavaBolt {
public:
    const static std::string ClassName;
    static java::Class& GetDefaultClass();

    JavaBolt(java::Class clazz, const std::string& className);
    JavaBolt(const std::string& className);

    JavaBolt* Clone();
    void Prepare();
    void Cleanup();
    void NextTuple();
    std::vector<std::string> DeclareFields();

private:
    java::Class _clazz;
    std::string _className;
    jobject _object;

    java::Method _constructMethod;
    java::Method _prepareMethod;
    java::Method _cleanupMethod;
    java::Method _nextTupleMethod;
    java::Method _declareFieldsMethod;
};

}
}

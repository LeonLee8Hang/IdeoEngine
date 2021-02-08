#pragma once

#include "ideoengine/multilang/java/Class.h"
#include "ideoengine/multilang/java/Object.h"
#include "ideoengine/base/Values.h"

namespace ideoengine {
namespace collector {

class OutputCollector;

class JavaOutputCollector : public java::Object {
public:
    const static std::string ClassName;
    static java::Class& GetDefaultClass();

    JavaOutputCollector(java::Class clazz, OutputCollector* outputCollector = nullptr);
    JavaOutputCollector(OutputCollector* outputCollector = nullptr);

    void Emit(const base::Tuple& tuple);

    jobject GetObject() {
        return _object;
    }

private:
    java::Class _clazz;
    jobject _object;
    OutputCollector* _outputCollector;

    java::Method _constructMethod;
};

}
}

ideoengine_JAVA_REGISTER_CLASS(ideoengine::collector::JavaOutputCollector, "ideoengine/jni/OutputCollector")



#pragma once

#include "ideoengine/multilang/java/String.h"
#include "ideoengine/multilang/java/Array.h"
#include "ideoengine/multilang/java/Class.h"
#include "ideoengine/spout/ISpout.h"

#include <jni.h>
#include <string>

namespace ideoengine {

namespace collector {
class OutputCollector;
class JavaOutputCollector;
}

namespace spout {

class JavaSpout : public ISpout {
public:
    const static std::string ClassName;
    static java::Class& GetDefaultClass();

    JavaSpout(java::Class clazz, const std::string& className);
    JavaSpout(const std::string& className);

    JavaSpout* Clone();
    virtual void Prepare(std::shared_ptr<ideoengine::collector::OutputCollector> outputCollector);
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

    collector::JavaOutputCollector* _collector;
    std::shared_ptr<ideoengine::collector::OutputCollector> _innerCollector;
};

}
}

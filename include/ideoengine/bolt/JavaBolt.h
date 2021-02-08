#pragma once
#include "ideoengine/multilang/java/String.h"
#include "ideoengine/multilang/java/Array.h"
#include "ideoengine/multilang/java/Class.h"
#include "ideoengine/bolt/IBolt.h"

#include <jni.h>
#include <string>

namespace ideoengine {

namespace collector {
class OutputCollector;
class JavaOutputCollector;
}

namespace bolt {

class JavaBolt : public IBolt {
public:
    const static std::string ClassName;
    static java::Class& GetDefaultClass();

    JavaBolt(java::Class clazz, const std::string& className);
    JavaBolt(const std::string& className);

    JavaBolt* Clone();
    void Prepare(std::shared_ptr<ideoengine::collector::OutputCollector> outputCollector);
    void Cleanup();
    void Execute(const ideoengine::base::Tuple& tuple);
    std::vector<std::string> DeclareFields();

private:
    java::Class _clazz;
    std::string _className;
    jobject _object;

    java::Method _constructMethod;
    java::Method _prepareMethod;
    java::Method _cleanupMethod;
    java::Method _executeMethod;
    java::Method _declareFieldsMethod;

    collector::JavaOutputCollector* _collector;
    std::shared_ptr<ideoengine::collector::OutputCollector> _innerCollector;
};

}
}

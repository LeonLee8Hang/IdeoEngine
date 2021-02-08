#include "ideoengine/collector/JavaOutputCollector.h"
#include "ideoengine/multilang/java/VirtualMachine.h"
#include "ideoengine/multilang/java/SignatureImpl.h"
#include "ideoengine/multilang/java/Signature.h"
#include "ideoengine/collector/OutputCollector.h"

#include <iostream>

namespace ideoengine {
namespace collector {

using java::Class;
using java::Method;
using java::VirtualMachine;
using java::Signature;

const std::string JavaOutputCollector::ClassName = "ideoengine/jni/OutputCollector";

static const std::string ConstructorMethodName = "<init>";

java::Class& JavaOutputCollector::GetDefaultClass()
{
    static Class collectorClass = VirtualMachine::GetDefault()->FindClass(JavaOutputCollector::ClassName);

    return collectorClass;
}

JavaOutputCollector::JavaOutputCollector(java::Class clazz, OutputCollector* outputCollector) :
    _clazz(clazz), _outputCollector(outputCollector)
{
    std::string constructSig = Signature::ForMethod<void, jlong>(
                HJARG(jlong));
    _constructMethod = _clazz.GetMethod(ConstructorMethodName, constructSig);
    _object = _clazz.NewObject(_constructMethod, reinterpret_cast<jlong>(this));
}

JavaOutputCollector::JavaOutputCollector(OutputCollector* outputCollector) :
    JavaOutputCollector(GetDefaultClass(), outputCollector)
{

}

void JavaOutputCollector::Emit(const base::Tuple& tuple)
{
    if ( _outputCollector ) {
        _outputCollector->Emit(tuple);
    }
}


}
}

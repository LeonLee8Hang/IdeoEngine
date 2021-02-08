

#include "ideoengine/spout/JavaSpout.h"
#include "ideoengine/collector/JavaOutputCollector.h"
#include "ideoengine/multilang/java/VirtualMachine.h"
#include "ideoengine/multilang/java/Signature.h"

namespace ideoengine {
namespace spout {

using java::Array;
using java::String;
using java::Class;
using java::Method;
using java::VirtualMachine;
using java::Signature;
using collector::JavaOutputCollector;

const std::string JavaSpout::ClassName = "ideoengine/jni/ISpout";

static const std::string ConstructorMethodName = "<init>";
static const std::string PrepareMethodName = "prepare";
static const std::string CleanupMethodName = "cleanup";
static const std::string NextTupleMethodName = "nextTuple";
static const std::string DeclareFieldsMethodName = "declareFields";

Class& JavaSpout::GetDefaultClass()
{
    std::cerr << "alsdjfkal" << std::endl;
    static Class boltClass = VirtualMachine::GetDefault()->FindClass(JavaSpout::ClassName);
    std::cerr << "kasljfl" << std::endl;

    return boltClass;
}

JavaSpout::JavaSpout(java::Class clazz, const std::string& className) :
    _clazz(clazz), _className(className)
{
    std::string constructSig = Signature::ForMethod<void>();
    std::string prepareSig = Signature::ForMethod<void, JavaOutputCollector>(
                HJARG(JavaOutputCollector));
    std::string cleanupSig = Signature::ForMethod<void>();
    std::string nextTupleSig = Signature::ForMethod<void>();
    std::string declareFieldsSig = Signature::ForMethod<Array<String>>();

    _constructMethod = _clazz.GetMethod(ConstructorMethodName, constructSig);
    _prepareMethod = _clazz.GetMethod(PrepareMethodName, prepareSig);
    _cleanupMethod = _clazz.GetMethod(CleanupMethodName, cleanupSig);
    _nextTupleMethod = _clazz.GetMethod(NextTupleMethodName, nextTupleSig);
    _declareFieldsMethod = _clazz.GetMethod(DeclareFieldsMethodName, declareFieldsSig);

    _object = _clazz.NewObject(_constructMethod);
}

JavaSpout::JavaSpout(const std::string& className) :
        JavaSpout(VirtualMachine::GetDefault()->FindClass(className), className)
{
}

JavaSpout* JavaSpout::Clone()
{
    return new JavaSpout(_clazz, _className);
}

void JavaSpout::Prepare(std::shared_ptr<collector::OutputCollector> outputCollector)
{
    _innerCollector = outputCollector;
    _collector = new JavaOutputCollector(outputCollector.get());
    _clazz.CallVoidMethod(_object, _prepareMethod, _collector->GetObject());
}

void JavaSpout::Cleanup()
{
    _clazz.CallVoidMethod(_object, _cleanupMethod);
}

void JavaSpout::NextTuple()
{
    LOG(LOG_DEBUG) << "Next tuple";
    _clazz.CallVoidMethod(_object, _nextTupleMethod);
}

std::vector<std::string> JavaSpout::DeclareFields()
{
    Array<String> javaFields = _clazz.CallArrayMethod<Array<String>>(
                _object, _declareFieldsMethod);

    size_t size = javaFields.GetSize();
    std::vector<std::string> fields(size);
    for ( int i = 0; i != javaFields.GetSize(); ++ i ) {
        fields[i] = javaFields[i].ToStdString();
    }

    return fields;
}

}

}

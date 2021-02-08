

#include "ideoengine/collector/JavaOutputCollector.jni.h"
#include "ideoengine/collector/JavaOutputCollector.h"
#include "ideoengine/multilang/java/NativeObjectWrapper.h"
#include "ideoengine/multilang/java/String.h"
#include "ideoengine/multilang/java/Signature.h"
#include "ideoengine/multilang/java/SignatureImpl.h"
#include "ideoengine/base/Values.h"

using ideoengine::java::NativeObjectWrapper;
using ideoengine::java::Signature;
using ideoengine::java::String;
using ideoengine::collector::JavaOutputCollector;
using ideoengine::base::Tuple;
using ideoengine::java::ToBoolean;
using ideoengine::java::FromBoolean;
using ideoengine::java::ToCharacter;
using ideoengine::java::FromCharacter;
using ideoengine::java::ToByte;
using ideoengine::java::FromByte;
using ideoengine::java::ToShort;
using ideoengine::java::FromShort;
using ideoengine::java::ToInteger;
using ideoengine::java::FromInteger;
using ideoengine::java::ToLong;
using ideoengine::java::FromLong;
using ideoengine::java::ToFloat;
using ideoengine::java::FromFloat;
using ideoengine::java::ToDouble;
using ideoengine::java::FromDouble;
using ideoengine::java::JAVA_BOOLEAN_CLASS;
using ideoengine::java::JAVA_BYTE_CLASS;
using ideoengine::java::JAVA_CHAR_CLASS;
using ideoengine::java::JAVA_SHORT_CLASS;
using ideoengine::java::JAVA_INT_CLASS;
using ideoengine::java::JAVA_LONG_CLASS;
using ideoengine::java::JAVA_FLOAT_CLASS;
using ideoengine::java::JAVA_DOUBLE_CLASS;
using ideoengine::java::JAVA_STRING_CLASS;

JNIEXPORT void JNICALL Java_ideoengine_jni_OutputCollector_emit
  (JNIEnv* env, jobject object, jobjectArray args) {
    NativeObjectWrapper hjni(env, object);
    Tuple tuple;

    jsize argSize = env->GetArrayLength(args);
    for ( int argIndex = 0; argIndex != argSize; ++ argIndex ) {
        jobject arg = env->GetObjectArrayElement(args, argIndex);
        jclass cls = env->GetObjectClass(arg);
        std::string className = NativeObjectWrapper::GetClassName(env, cls);

        if ( className == JAVA_BOOLEAN_CLASS ) {
            tuple.Add({ FromBoolean(env, object) });
        }
        else if ( className == JAVA_CHAR_CLASS ) {
            tuple.Add({ FromCharacter(env, object) });
        }
        else if ( className == JAVA_BYTE_CLASS ) {
            tuple.Add({ FromByte(env, object) });
        }
        else if ( className == JAVA_SHORT_CLASS ) {
            tuple.Add({ FromShort(env, object) });
        }
        else if ( className == JAVA_INT_CLASS ) {
            tuple.Add({ FromInteger(env, object) });
        }
        else if ( className == JAVA_LONG_CLASS ) {
            tuple.Add({ FromLong(env, object) });
        }
        else if ( className == JAVA_FLOAT_CLASS ) {
            tuple.Add({ FromFloat(env, object) });
        }
        else if ( className == JAVA_STRING_CLASS ) {
            String data(object);
            tuple.Add({ data.ToStdString() });
        }
    }

    hjni.CallVoidMethod<JavaOutputCollector>(&JavaOutputCollector::Emit, tuple);
}

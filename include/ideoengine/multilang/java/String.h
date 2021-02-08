

#pragma once

#include "ideoengine/multilang/java/Class.h"
#include "ideoengine/multilang/java/Object.h"
#include <jni.h>

namespace ideoengine {
namespace java {

class String : public Object {
public:
    const static std::string ClassName;
    static Class& GetDefaultClass();

    String(const Class& clazz);
    String(const Class& clazz, const std::string& data);
    String();
    String(const std::string& data);
    String(jstring data);
    String(jobject data);

    const std::string& ToStdString() const {
        return _data;
    }

    void SetData(const std::string& data) {
        _data = data;
    }

    jstring ToJavaString() const;

private:
    Class _clazz;
    jstring _object;
    std::string _data;
};

}
}

ideoengine_JAVA_REGISTER_CLASS(ideoengine::java::String, "java/lang/String")

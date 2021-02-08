

#pragma once

#include <jni.h>

#include <vector>
#include <string>
#include <cstdint>

namespace ideoengine {
namespace java {

class Class;

class VirtualMachine {
public:
    static VirtualMachine* GetDefault() {
        return _DefaultVM;
    }

    static void SetDefault(VirtualMachine* vm) {
        _DefaultVM = vm;
    }

public:
    VirtualMachine(int32_t version = JNI_VERSION_1_6) :
        _vm(nullptr), _env(nullptr), _version(version) {
    }

    ~VirtualMachine();

    JavaVM* GetVM() {
        return _vm;
    }

    const JavaVM* GetVM() const {
        return _vm;
    }

    JNIEnv* GetEnv();
    const JNIEnv* GetEnv() const {
        return _env;
    }

    void SetVersion(int32_t version) {
        _version = version;
    }

    int32_t GetVersion() {
        return _version;
    }

    void SetClassPaths(const std::vector<std::string>& classPaths) {
        _classPaths = classPaths;
    }

    const std::vector<std::string>& GetClassPaths() const {
        return _classPaths;
    }

    void AddClassPath(const std::string& classPath);
    void Start();
    Class FindClass(const std::string& className);

private:
    static VirtualMachine* _DefaultVM;

private:
    JavaVM* _vm;
    JNIEnv* _env;
    int32_t _version;
    std::vector<std::string> _classPaths;
};

}
}

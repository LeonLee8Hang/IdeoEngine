

#include "ideoengine/multilang/java/Class.h"
#include "ideoengine/multilang/java/VirtualMachine.h"

#include <iostream>

namespace ideoengine {
namespace java {

Class Class::ForName(const std::string& className)
{
    return VirtualMachine::GetDefault()->FindClass(className);
}

Class::Class(VirtualMachine* vm, const std::string& className, jclass clazz) :
    _vm(vm), _env(vm->GetEnv()), _className(className), _clazz(clazz)
{
}

}
}

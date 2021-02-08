

#include "ideoengine/bolt/BoltDeclarer.h"
#include "ideoengine/bolt/IBolt.h"

namespace ideoengine {
namespace bolt {

BoltDeclarer::BoltDeclarer(const std::string& boltName, IBolt* bolt) :
    _bolt(bolt){
    SetType(ideoengine::task::TaskDeclarer::Type::Bolt);
    SetTaskName(boltName);

    _fields = _bolt->DeclareFields();
    int32_t fieldIndex = 0;
    for ( const std::string& field : _fields ) {
        _fieldsMap.insert({field, fieldIndex});
    }
}

BoltDeclarer& BoltDeclarer::ParallismHint(int32_t parallismHint) {
    SetParallismHint(parallismHint);

    return *this;
}

BoltDeclarer& BoltDeclarer::Global(const std::string& sourceTaskName) {
    SetSourceTaskName(sourceTaskName);
    SetGroupMethod(ideoengine::task::TaskDeclarer::GroupMethod::Global);

    return *this;
}

BoltDeclarer& BoltDeclarer::Field(const std::string& sourceTaskName, const std::string& groupField) {
    SetSourceTaskName(sourceTaskName);
    SetGroupMethod(ideoengine::task::TaskDeclarer::GroupMethod::Field);
    SetGroupField(groupField);

    return *this;
}

BoltDeclarer& BoltDeclarer::Random(const std::string& sourceTaskName) {
    SetSourceTaskName(sourceTaskName);
    SetGroupMethod(ideoengine::task::TaskDeclarer::GroupMethod::Random);

    return *this;
}

}
}

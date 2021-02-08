

#include "ideoengine/message/Command.h"
#include "ideoengine/base/DataPackage.h"
#include "logging/Logging.h"

#include <iostream>

namespace ideoengine {
namespace message {

Command::Command(int32_t type) : _type(type) {
}

Command::Command(int32_t type, std::vector<ideoengine::base::Variant>& arguments) :
    _type(type), _arguments(arguments) {
}

void Command::AddArgument(const ideoengine::base::Variant& argument) {
    _arguments.push_back(argument);
}

void Command::AddArguments(const std::vector<ideoengine::base::Variant>& arguments) {
    for ( const ideoengine::base::Variant& argument : arguments ) {
        _arguments.push_back(argument);
    }
}

void Command::Deserialize(const ideoengine::base::ByteArray& data) {
    ideoengine::base::DataPackage dataPackage;
    dataPackage.Deserialize(data);

    if ( !dataPackage.GetVariants().size() ) {
        LOG(LOG_ERROR) << "Data package error";
    }

    _arguments = dataPackage.GetVariants();
    _type = _arguments[0].GetInt32Value();
    _arguments.erase(_arguments.begin());
}

ideoengine::base::ByteArray Command::Serialize() const {
    ideoengine::base::DataPackage dataPackage;

    dataPackage.AddVariant(ideoengine::base::Variant(_type));
    for ( const ideoengine::base::Variant& argument : _arguments ) {
        dataPackage.AddVariant(argument);
    }

    return dataPackage.Serialize();
}

Response::Response(int32_t status) : _status(status) {
}

Response::Response(int32_t status, std::vector<ideoengine::base::Variant>& arguments) :
    _status(status), _arguments(arguments) {
}

void Response::AddArguments(const std::vector<ideoengine::base::Variant>& arguments) {
    for ( const ideoengine::base::Variant& argument : arguments ) {
        _arguments.push_back(argument);
    }
}

void Response::AddArgument(const ideoengine::base::Variant& argument) {
    _arguments.push_back(argument);
}

void Response::Deserialize(const ideoengine::base::ByteArray& data) {
    ideoengine::base::DataPackage dataPackage;
    dataPackage.Deserialize(data);

    if ( !dataPackage.GetVariants().size() ) {
        LOG(LOG_ERROR) << "Data package error";
    }

    _arguments = dataPackage.GetVariants();
    _status = _arguments[0].GetInt32Value();
    _arguments.erase(_arguments.begin());
}

ideoengine::base::ByteArray Response::Serialize() const {
    ideoengine::base::DataPackage dataPackage;

    dataPackage.AddVariant(ideoengine::base::Variant(_status));
    for ( const ideoengine::base::Variant& argument : _arguments ) {
        dataPackage.AddVariant(argument);
    }

    return dataPackage.Serialize();
}

}
}

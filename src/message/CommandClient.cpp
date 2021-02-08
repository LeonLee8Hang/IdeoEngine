

#include "ideoengine/message/CommandClient.h"
#include "ideoengine/message/Command.h"
#include "ideoengine/util/NetConnector.h"
#include "ideoengine/base/ByteArray.h"
#include "logging/Logging.h"

#include <iostream>

namespace ideoengine {
namespace message {

CommandClient::CommandClient(ideoengine::util::NetConnector* connector) : _connector(connector) {
}

CommandClient::~CommandClient() {
    if ( _connector ) {
        delete _connector;
        _connector = nullptr;
    }
}

void CommandClient::Connect(CommandClient::ConnectCallback callback)
{
    this->_connector->Connect([callback](const util::SocketError& error) {
        if ( error.GetType() != util::SocketError::Type::NoError ) {
            callback(CommandError(CommandError::Type::ConnectError,
                                  error.what()));
            return;
        }

        callback(CommandError());
    });
}

void CommandClient::SendCommand(const Command& command, SendCommandCallback callback) {
    try {
        ideoengine::base::ByteArray commandBytes = command.Serialize();

        _connector->SendAndReceive(commandBytes.data(), static_cast<int32_t>(commandBytes.size()), [callback]
                                   (char* resultBuffer, int32_t readSize, const util::SocketError& error) {
            ideoengine::message::Response response;

            if ( error.GetType() != util::SocketError::Type::NoError ) {
                callback(response, CommandError(CommandError::Type::SendError,
                                                error.what()));
                return;
            }

            ideoengine::base::ByteArray commandBytes(resultBuffer, readSize);
            response.Deserialize(commandBytes);
            callback(response, CommandError());
        });
    }
    catch (const char* message) {
        LOG(LOG_ERROR) << message;
    }
}
}
}

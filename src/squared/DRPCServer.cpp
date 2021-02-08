

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "ideoengine/base/NetAddress.h"
#include "ideoengine/base/ByteArray.h"
#include "ideoengine/base/DataPackage.h"
#include "temp/NetListener.h"
#include "ideoengine/message/CommandDispatcher.h"
#include "ideoengine/message/PresidentCommander.h"
#include "ideoengine/base/Node.h"
#include "temp/WordCountTopology.h"
#include "DRPCStream.h"

using ideoengine::base::NetAddress;
using ideoengine::base::ByteArray;
using ideoengine::base::DataPackage;
using ideoengine::message::Command;
using ideoengine::message::CommandDispatcher;
using ideoengine::message::PresidentCommander;
using ideoengine::base::Node;
using ideoengine::topology::ITopology;
using ideoengine::spout::ISpout;
using ideoengine::bolt::IBolt;
using ideoengine::squared::DRPCStream;

const NetAddress SERVER_ADDRESS{ "127.0.0.1", 3772 };

int main() {
    NetListener netListener(SERVER_ADDRESS);
    CommandDispatcher dispatcher;
    std::map<std::string, DRPCStream*> streams;
    
    dispatcher
        .OnCommand(Command::Type::Join,
            [&](ideoengine::base::Variants args, std::shared_ptr<TcpConnection> src) -> void {
        std::string serviceName = args[0].GetStringValue();
        args.pop_front();
        std::string serviceArgs = args;

        DRPCStream* stream = streams[serviceName];
        std::string result = stream->WaitFormResult(args);

        Command command(Command::Type::Response, {
            result
        });

        ByteArray commandBytes = command.ToDataPackage().Serialize();
        src->Send(commandBytes.data(), commandBytes.size());
    });

    netListener.OnData([&](std::shared_ptr<TcpConnection> connection,
        const char* buffer, int32_t size) -> void {
        ByteArray receivedData(buffer, size);
        DataPackage receivedPackage;
        receivedPackage.Deserialize(receivedData);

        Command command(receivedPackage);
        command.SetSrc(connection);

        dispatcher.Dispatch(command);
    });

    netListener.StartListen();
}
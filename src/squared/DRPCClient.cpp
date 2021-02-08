

#include "DRPCClient.h"
#include "ideoengine/base/ByteArray.h"
#include "ideoengine/base/DataPackage.h"
#include "ideoengine/message/Command.h"
#include "ideoengine/message/PresidentCommander.h"
#include "logging/Logging.h"

using ideoengine::base::NetAddress;
using ideoengine::base::ByteArray;
using ideoengine::base::DataPackage;
using ideoengine::message::Command;

const int32_t DATA_BUFFER_SIZE = 65535;

namespace ideoengine {
    namespace squared {
        std::string DRPCClient::Execute(const std::string & serviceName, ideoengine::base::Values & values)
        {
            Connect();

            Command command(Command::Type::StartSpout, {
                serviceName
            } + values.ToVariants());

            DataPackage messagePackage = command.ToDataPackage();
            ByteArray message = messagePackage.Serialize();

            char resultBuffer[DATA_BUFFER_SIZE];
            int32_t resultSize =
                _connector->SendAndReceive(message.data(), message.size(), resultBuffer, DATA_BUFFER_SIZE);

            ByteArray result(resultBuffer, resultSize);
            DataPackage resultPackage;
            resultPackage.Deserialize(result);
            command = Command(resultPackage);

           sstd::coutDEBUG) << command.GetType() << std::endl;
            LOG(LOG_DEBUG) << command.GetArg(0).GetStringValue() << std::endl;

            return command.GetArg(0).GetStringValue();
        }
    }
}

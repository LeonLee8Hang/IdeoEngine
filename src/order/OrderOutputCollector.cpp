#include "ideoengine/order/OrderOutputCollector.h"
#include "ideoengine/collector/OutputCollector.h"
#include "ideoengine/service/Manager.h"
#include "ideoengine/message/CommandClient.h"
#include "ideoengine/util/NetConnector.h"

namespace ideoengine {
namespace order {

OrderOutputCollector::OrderOutputCollector(std::shared_ptr<collector::OutputCollector> collector) :
        _collector(collector){
}

void OrderOutputCollector::Emit(const OrderTuple& tuple)
{
    service::Manager* manager = service::Manager::GetGlobalInstance();

    message::CommandClient* commandClient = manager->CreatePresidentClient();

    if ( tuple.GetOrderId() == 0 ) {
        commandClient->GetConnector()->Connect([this, manager, commandClient, tuple]
        (const util::SocketError& socketError) {
            if ( socketError.GetType() != util::SocketError::Type::NoError ) {
                LOG(LOG_ERROR) << socketError.what();
                return;
            }

            ideoengine::message::Command command(ideoengine::message::Command::Type::OrderId);
            command.AddArgument({ manager->GetTopologyName() });

            commandClient->SendCommand(command,
                [this, manager, tuple](const ideoengine::message::Response& response,
                        const message::CommandError& error) -> void {
                if ( error.GetType() != message::CommandError::Type::NoError ) {
                    LOG(LOG_ERROR) << error.what();
                    return;
                }

                if ( response.GetStatus() == ideoengine::message::Response::Status::Successful ) {
                    int64_t orderId = response.GetArgument(0).GetInt64Value();
                    OrderTuple newTuple = tuple;
                    newTuple.SetOrderId(orderId);
                    _collector->Emit(newTuple.ToBaseTuple());
                }
                else {
                    LOG(LOG_ERROR) << "Get new order id of " << manager->GetTopologyName() << " failed.";
                }
            });
        });
    }
    else {
        _collector->Emit(tuple.ToBaseTuple());
    }

}


}
}

#include "ideoengine/order/OrderSpout.h"
#include "ideoengine/order/OrderOutputCollector.h"

void ideoengine::order::OrderSpout::Prepare(
        std::shared_ptr<ideoengine::collector::OutputCollector> outputCollector)
{
    std::shared_ptr<ideoengine::order::OrderOutputCollector> orderCollector =
            std::make_shared<ideoengine::order::OrderOutputCollector>(outputCollector);

    Prepare(orderCollector);
}

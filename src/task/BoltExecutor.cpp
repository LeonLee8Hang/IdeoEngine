

#include "ideoengine/task/BoltExecutor.h"
#include "ideoengine/bolt/IBolt.h"
#include "ideoengine/collector/TaskQueue.h"

namespace ideoengine {
namespace task {

BoltExecutor::BoltExecutor()
{
}

void BoltExecutor::Start()
{
    // It is managed by main thread, so we don't need to detach it
    _thread = std::thread(&BoltExecutor::StartLoop, this);
}

void BoltExecutor::StartLoop()
{
    collector::TaskItem* taskItem;

    while ( _taskQueue->Pop(taskItem) ) {
        _bolt->Execute(taskItem->GetTuple());

        delete taskItem;
        taskItem = nullptr;
    }
}


}
}

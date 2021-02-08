

#pragma once

#include "ideoengine/task/ITask.h"
#include "ideoengine/base/Values.h"

namespace ideoengine {
namespace spout {

class ISpout : public ideoengine::task::ITask {
public:
    virtual ISpout* Clone() = 0;
    virtual void NextTuple() = 0;
};

}
}

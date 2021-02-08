#pragma once

#include "ideoengine/task/ITask.h"
#include "ideoengine/base/Values.h"

namespace ideoengine {
namespace bolt {

class IBolt : public ideoengine::task::ITask {
public:
    virtual IBolt* Clone() = 0;
    virtual void Execute(const ideoengine::base::Tuple& tuple) = 0;
};

}
}

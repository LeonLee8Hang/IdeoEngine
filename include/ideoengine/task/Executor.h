

#pragma once

namespace ideoengine {
namespace task {

class Executor {
public:
    struct MessageType {
        enum {
            OnTuple
        };
    };

    virtual ~Executor() {}

    virtual void Start() = 0;
};

}
}

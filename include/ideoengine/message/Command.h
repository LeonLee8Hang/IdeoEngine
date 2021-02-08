#pragma once

#include <string>
#include <vector>
#include "ideoengine/base/ByteArray.h"
#include "ideoengine/base/Variant.h"

namespace ideoengine {
namespace message {
class Command {
public:
    struct Type {
        enum {
            Invalid = 0,
            Join,
            Heartbeat,
            SyncMetadata,
            SendTuple,
            AskField,
            OrderId
        };
    };

    Command(int32_t type = Type::Invalid);
    Command(int32_t type, std::vector<ideoengine::base::Variant>& arguments);

    void AddArgument(const ideoengine::base::Variant& argument);
    void AddArguments(const std::vector<ideoengine::base::Variant>& arguments);

    void Deserialize(const ideoengine::base::ByteArray& data);
    ideoengine::base::ByteArray Serialize() const;

    int32_t GetType() const {
        return _type;
    }

    void SetType(int32_t type) {
        _type = type;
    }

    ideoengine::base::Variant GetArgument(int32_t index) const {
        return _arguments[index];
    }

    int32_t GetArgumentCount() const {
        return static_cast<int32_t>(_arguments.size());
    }

    const std::vector<ideoengine::base::Variant>& GetArguments() const {
        return _arguments;
    }

private:
    int32_t _type;
    std::vector<ideoengine::base::Variant> _arguments;
};

class Response {
public:
    struct Status {
        enum {
            Failed = 0,
            Successful = 1
        };
    };

    Response(int32_t status = Status::Failed);
    Response(int32_t status, std::vector<ideoengine::base::Variant>& arguments);

    void AddArguments(const std::vector<ideoengine::base::Variant>& arguments);
    void AddArgument(const ideoengine::base::Variant& argument);

    void Deserialize(const ideoengine::base::ByteArray& data);
    ideoengine::base::ByteArray Serialize() const;

    int32_t GetStatus() const {
        return _status;
    }

    void SetStatus(int32_t status) {
        _status = status;
    }

    ideoengine::base::Variant GetArgument(int32_t index) const {
        return _arguments[index];
    }

    int32_t GetArgumentCount() const {
        return static_cast<int32_t>(_arguments.size());
    }

    const std::vector<ideoengine::base::Variant>& GetArguments() const {
        return _arguments;
    }

private:
    int32_t _status;
    std::vector<ideoengine::base::Variant> _arguments;
};
}
}

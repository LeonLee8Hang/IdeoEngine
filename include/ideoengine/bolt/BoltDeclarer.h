#pragma once

#include "ideoengine/task/TaskDeclarer.h"
#include <memory>
#include <string>
#include <map>
#include <vector>

namespace ideoengine {
namespace bolt {
class IBolt;

class BoltDeclarer : public ideoengine::task::TaskDeclarer {
public:
    BoltDeclarer() = default;
    BoltDeclarer(const std::string& boltName, IBolt* bolt);

    BoltDeclarer& ParallismHint(int32_t parallismHint);
    BoltDeclarer& Global(const std::string& sourceTaskName);
    BoltDeclarer& Field(const std::string& sourceTaskName, const std::string& groupField);
    BoltDeclarer& Random(const std::string& sourceTaskName);

    const std::string& GetGroupField() const {
        return _groupField;
    }

    void SetGroupField(const std::string& groupField) {
        _groupField = groupField;
    }

    std::shared_ptr<IBolt> GetBolt() const {
        return _bolt;
    }

    const std::vector<std::string>& GetFields() const {
        return _fields;
    }

    const std::map<std::string, int32_t>& GetFieldsMap() const {
        return _fieldsMap;
    }

private:
    std::shared_ptr<IBolt> _bolt;
    std::string _groupField;
    std::vector<std::string> _fields;
    std::map<std::string, int32_t> _fieldsMap;
};
}
}

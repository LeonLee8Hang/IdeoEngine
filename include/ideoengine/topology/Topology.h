#pragma once

#include "ideoengine/spout/SpoutDeclarer.h"
#include "ideoengine/bolt/BoltDeclarer.h"

#include <memory>
#include <map>
#include <string>

namespace ideoengine {
namespace spout {
class ISpout;
}

namespace bolt {
class IBolt;
}

namespace topology {
class Topology {
public:
    Topology(const std::string& name);

    ideoengine::spout::SpoutDeclarer& SetSpout(const std::string& spoutName, ideoengine::spout::ISpout* spout);
    ideoengine::bolt::BoltDeclarer& SetBolt(const std::string& boltName, ideoengine::bolt::IBolt* bolt);

    const std::string& GetName() const {
        return _name;
    }

    const std::map<std::string, ideoengine::spout::SpoutDeclarer>& GetSpoutDeclarers() const {
        return _spoutDeclarers;
    }

    const std::map<std::string, ideoengine::bolt::BoltDeclarer>& GetBoltDeclarers() const {
        return _boltDeclarers;
    }

private:
    std::string _name;
    std::map<std::string, ideoengine::spout::SpoutDeclarer> _spoutDeclarers;
    std::map<std::string, ideoengine::bolt::BoltDeclarer> _boltDeclarers;
};

}
}

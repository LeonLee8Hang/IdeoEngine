

#include "ideoengine/topology/Topology.h"

namespace ideoengine {
    namespace topology {
        Topology::Topology(const std::string& name) : _name(name) {
        }

        ideoengine::spout::SpoutDeclarer& Topology::SetSpout(const std::string& spoutName, ideoengine::spout::ISpout* spout) {
            _spoutDeclarers.insert({ spoutName, ideoengine::spout::SpoutDeclarer(spoutName, spout) });

            return _spoutDeclarers[spoutName];
        }

        ideoengine::bolt::BoltDeclarer& Topology::SetBolt(const std::string& boltName, ideoengine::bolt::IBolt* bolt) {
            _boltDeclarers.insert({ boltName, ideoengine::bolt::BoltDeclarer(boltName, bolt) });

            return _boltDeclarers[boltName];
        }
    }
}

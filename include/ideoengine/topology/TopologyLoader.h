#pragma once

#include "ideoengine/topology/Topology.h"
#include "ideoengine/base/Library.h"
#include <map>
#include <string>
#include <memory>

namespace ideoengine {
namespace topology {
class Topology;

class TopologyLoader {
public:
    typedef Topology* (*TopologyGetter)();

    static TopologyLoader& GetInstance();
    std::shared_ptr<Topology> GetTopology(const std::string& name);

private:
    TopologyLoader() {}
    TopologyLoader(const TopologyLoader& loader) = delete;
    const TopologyLoader& operator = (const TopologyLoader& loader) = delete;

    std::map<std::string, std::shared_ptr<Topology>> _topologies;
    std::map<std::string, LibraryHandle> _libraryHandles;
};
}
}

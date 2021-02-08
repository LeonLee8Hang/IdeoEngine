

#include "ideoengine/topology/TopologyLoader.h"
#include "ideoengine/base/Library.h"
#include "logging/Logging.h"

namespace ideoengine {
namespace topology {
const std::string& GET_TOPOLOGY_INTERFACE = "GetTopology";

TopologyLoader& TopologyLoader::GetInstance() {
    static TopologyLoader instance;

    return instance;
}

std::shared_ptr<Topology> TopologyLoader::GetTopology(const std::string& topologyName) {
    if ( _libraryHandles.find(topologyName) == _libraryHandles.end() ) {
        LibraryHandle libraryHandle = ideoengineLibraryLoad(topologyName);
        _libraryHandles[topologyName] = libraryHandle;
        TopologyGetter topologyGetter =
                ideoengineLibraryGetSymbol<TopologyGetter>(libraryHandle, GET_TOPOLOGY_INTERFACE);

        _topologies[topologyName].reset(topologyGetter());
    }

    return _topologies[topologyName];
}

}
}

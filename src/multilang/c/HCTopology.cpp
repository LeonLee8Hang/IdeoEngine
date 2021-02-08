

#include "ideoengine/multilang/c/HCTopology.h"
#include "ideoengine/multilang/c/HCSpout.h"
#include "ideoengine/multilang/c/HCBolt.h"
#include "ideoengine/topology/TopologyBuilder.h"
#include "ideoengine/topology/LocalTopology.h"
#include "ideoengine/topology/ITopology.h"

using ideoengine::topology::TopologyBuilder;
using ideoengine::topology::LocalTopology;
using ideoengine::topology::ITopology;
using ideoengine::spout::CSpoutWrapper;
using ideoengine::bolt::CBoltWrapper;

void StartTopology(CTopology * cTopology)
{
    LocalTopology localTopology;
    TopologyBuilder topologyBuilder;

    for ( int32_t spoutIndex = 0; spoutIndex < cTopology->spoutCount; spoutIndex ++  ) {
        topologyBuilder.SetSpout(cTopology->spoutNames[spoutIndex],
            new CSpoutWrapper(cTopology->cSpouts + spoutIndex));
    }

    for ( int32_t boltIndex = 0; boltIndex < cTopology->boltCount; boltIndex ++ ) {
        topologyBuilder.SetBolt(cTopology->boltNames[boltIndex],
            new CBoltWrapper(cTopology->cBolts + boltIndex),
            cTopology->boltSources[boltIndex]);
    }

    ITopology* topology = topologyBuilder.Build();
    localTopology.Submit("hello", std::shared_ptr<ITopology>(topology));

    std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 10));
}


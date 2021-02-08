

#pragma once

#include "ideoengine/topology/SimpleTopology.h"
#include <memory>
#include <map>

namespace ideoengine {
    namespace squared {
        class SquaredSpout;
        class SquaredStream;
        class DRPCStream;

        class SquaredToplogy : public SimpleTopology {
        public:
            SquaredToplogy SquaredToplogy();
            SquaredStream* NewStream(const std::string& spoutName,
                SquaredSpout* squaredSpout);

            DRPCStream* NewDRPCStream(const std::string& serviceName);

            void Deploy();
            
        private:
            void _Deploy(SquaredStream* stream);
            void _Deploy(DRPCStream* stream);

        private:
            std::vector<std::shared_ptr<SquaredStream>> _squaredStreams;
            std::map<std::string, std::shared_ptr<DRPCStream>> _drpcStreams;
        };
    }
}
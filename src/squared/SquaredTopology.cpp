

#include "SquaredTopology.h"
#include "SquaredSpout.h"
#include "SquaredStream.h"
#include "DRPCStream.h"

namespace ideoengine {
    namespace squared {
        SquaredToplogy::SquaredToplogy()
        {
        }

        SquaredStream * SquaredToplogy::NewStream(const std::string & spoutName,
            SquaredSpout * squaredSpout)
        {
            std::shared_ptr<SquaredStream> stream = 
                std::make_shared<SquaredStream>(spoutName, squaredSpout);

            _squaredStreams.push_back(stream);

            return stream.get();
        }

        DRPCStream * SquaredToplogy::NewDRPCStream(const std::string & serviceName)
        {
            std::shared_ptr<DRPCStream> stream = std::make_shared<DRPCStream>();
            _drpcStreams[serviceName] = stream;

            return stream.get();
        }

        void SquaredToplogy::Deploy()
        {
            for ( auto stream : _squaredStreams ) {
                _Deploy(stream);
            }

            for ( auto streamPair : _drpcStreams ) {
                _Deploy(stream);
            }
        }

        void SquaredToplogy::_Deploy(SquaredStream * stream)
        {
            stream->Deploy(this);
        }

        void SquaredToplogy::_Deploy(DRPCStream * stream)
        {
            stream->Deploy(this);
        }
    }
}


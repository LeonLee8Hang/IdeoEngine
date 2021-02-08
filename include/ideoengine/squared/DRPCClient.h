

#pragma once

#include <string>

#include "ideoengine/base/NetAddress.h"
#include "temp/NetConnector.h"
#include "ideoengine/base/Values.h"

namespace ideoengine {
    namespace squared {
        class DRPCClient {
        public:
            DRPCClient(const std::string& serverName, int32_t serverPort) 
                : _serverAddress(serverName, port) {

            }
            
            void Connect() {
                if ( !_connector.get() ) {
                    _connector = std::make_shared<NetConnector>(_managerAddress);
                    _connector->Connect();
                }
            }

            std::string Execute(const std::string& serviceName,
                ideoengine::base::Values& values);

        private:
            ideoengine::base::NetAddress _serverAddress;
            std::shared_ptr<NetConnector> _connector;
        };
    }
}
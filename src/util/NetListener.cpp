

#include "ideoengine/util/NetListener.h"
#include "logging/Logging.h"

#include <iostream>
#include <thread>
#include <chrono>

namespace ideoengine {
namespace util {

const int32_t DATA_BUFFER_SIZE = 65535;

NetListener::NetListener(const ideoengine::base::NetAddress& host) :
    _host(host) {
}

void NetListener::StartListen()
{
    _server = std::make_shared<TcpServer>();

    _server->Listen(_host.GetHost(), _host.GetPort());
    LOG(LOG_INFO) << "Listen on " << _host.GetHost() << ":" << _host.GetPort();

    while ( true )
    {
        std::shared_ptr<TcpConnection> connection = std::shared_ptr<TcpConnection>(_server->Accept());

        LOG(LOG_ERROR) << "A client is connected";

        std::thread dataThread(std::bind(&NetListener::DataThreadMain, this, std::placeholders::_1),
                               connection);
        dataThread.detach();
    }
}

void NetListener::DataThreadMain(std::shared_ptr<TcpConnection> connection)
{
    int32_t _lostTime = 0;

    _connectionCallback(connection);

    try {
        char buffer[DATA_BUFFER_SIZE];
        while ( true ) {
            bool successful = connection->ReceiveAsync(buffer, DATA_BUFFER_SIZE);

            if ( !successful ) {
                break;
            }
        }
    }
    catch ( const std::exception& e ) {
        LOG(LOG_ERROR) << e.what();
    }
}

void NetListener::OnConnection(ConnectionCallback callback) {
    _connectionCallback = callback;
}

}
}

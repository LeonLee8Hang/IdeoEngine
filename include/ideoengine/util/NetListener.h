

#pragma once

#include "ideoengine/util/Socket.h"
#include "ideoengine/base/NetAddress.h"
#include <functional>
#include <cstdint>

#include <memory>

namespace ideoengine {
namespace util {
typedef std::function<void(std::shared_ptr<TcpConnection> connection)> ConnectionCallback;
typedef std::function<void(std::shared_ptr<TcpConnection> connection,
                           const char* buffer, int32_t size)>
DataReceiver;

class NetListener {
public:
    NetListener(const ideoengine::base::NetAddress& host);

    const ideoengine::base::NetAddress& GetHost() const {
        return _host;
    }

    void SetHost(const ideoengine::base::NetAddress& host) {
        _host = host;
    }

    void StartListen();
    void DataThreadMain(std::shared_ptr<TcpConnection> connection);
    void OnConnection(ConnectionCallback callback);

private:
    ideoengine::base::NetAddress _host;
    std::shared_ptr<TcpServer> _server;
    ConnectionCallback _connectionCallback;
};
}
}


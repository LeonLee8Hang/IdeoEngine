namespace ideoengine {
namespace message {

template <class CommandServerContext>
CommandServer<CommandServerContext>::CommandServer(ideoengine::util::NetListener* listener) :
    _listener(listener) {
}

template <class CommandServerContext>
CommandServer<CommandServerContext>::~CommandServer() {
    if ( _listener ) {
        delete _listener;
        _listener = nullptr;
    }
}

template <class CommandServerContext>
void CommandServer<CommandServerContext>::StartListen() {
    std::map<int32_t, CommandHandler>& commandHandlers = _commandHandlers;
    ConnectHandler connectHandler = _connectHandler;

    _listener->OnConnection([this, connectHandler, commandHandlers](std::shared_ptr<ideoengine::util::TcpConnection> connection) {
        CommandServerContext* context = new CommandServerContext;
        ideoengine::util::TcpConnection* rawConnection = connection.get();

        _connectHandler(context);

        connection->OnData([this, commandHandlers, context, rawConnection]
                           (const char* buffer, int32_t size, const util::SocketError& error) {
            if ( error.GetType() != util::SocketError::Type::NoError ) {
                LOG(LOG_ERROR) << error.what();
                return;
            }

            ideoengine::base::ByteArray commandBytes(buffer, size);
            Command command;
            command.Deserialize(commandBytes);

            int32_t commandType = command.GetType();
            try {
                CommandHandler handler = commandHandlers.at(commandType);
                Responsor Responsor = std::bind(&CommandServer::Response, this, rawConnection, std::placeholders::_1);

                handler(context, command, Responsor);
            }
            catch ( const std::exception& e ) {
                LOG(LOG_ERROR) << "Some errors in command handler";
                LOG(LOG_ERROR) << e.what();

                Responsor Responsor = std::bind(&CommandServer::Response, this, rawConnection, std::placeholders::_1);

                ideoengine::message::Response response(ideoengine::message::Response::Status::Failed);
                Responsor(response);
            }
        });
    });

    _listener->StartListen();
}

template <class CommandServerContext>
void CommandServer<CommandServerContext>::Response(ideoengine::util::TcpConnection* connection, const ideoengine::message::Response& response) {
    ideoengine::base::ByteArray responseBytes = response.Serialize();
    connection->Send(responseBytes.data(), responseBytes.size());
}

template <class CommandServerContext>
void CommandServer<CommandServerContext>::OnCommand(int32_t commandType, CommandHandler handler) {
    _commandHandlers.insert({ commandType, handler });
}

template <class CommandServerContext>
void CommandServer<CommandServerContext>::OnConnection(ConnectHandler handler) {
    _connectHandler = handler;
}

}
}

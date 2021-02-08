

#include "ideoengine/service/Manager.h"

#ifdef ENABLE_MULTILANG_JAVA
#include "ideoengine/multilang/java/VirtualMachine.h"
#endif // ENABLE_MULTILANG_JAVA

#include "ideoengine/util/Configuration.h"
#include "ideoengine/base/Constants.h"
#include "logging/Logging.h"

#include <iostream>
#include <string>
#include <csignal>

using namespace std;

void StartManager(const std::string& configFileName);
static void StartJVM(const ideoengine::util::Configuration& configuration);
static void ProcessSignal(int signalNumber);

int main(int argc, char* argv[])
{
    if ( argc < 2 ) {
        return EXIT_FAILURE;
    }

    StartManager(argv[1]);

    return EXIT_SUCCESS;
}

void StartManager(const std::string& configFileName) {
    ideoengine::util::Configuration managerConfiguration;
    managerConfiguration.Parse(configFileName);

    LOG(LOG_INFO) << managerConfiguration.GetProperty(ideoengine::CONF_KEY_PRESIDENT_HOST);
    LOG(LOG_INFO) << managerConfiguration.GetIntegerProperty(ideoengine::CONF_KEY_PRESIDENT_PORT);
    LOG(LOG_INFO) << managerConfiguration.GetProperty(ideoengine::CONF_KEY_MANAGER_HOST);
    LOG(LOG_INFO) << managerConfiguration.GetIntegerProperty(ideoengine::CONF_KEY_MANAGER_PORT);

#ifdef ENABLE_MULTILANG_JAVA
    if ( managerConfiguration.GetBooleanProperty(ideoengine::CONF_KEY_ENABLE_JAVA) ) {
        StartJVM(managerConfiguration);
    }
#endif // ENABLE_MULTILANG_JAVA

    signal(SIGINT, ProcessSignal);

    ideoengine::service::Manager manager(managerConfiguration);
    manager.JoinPresident([&manager](const ideoengine::message::Response& response) {
        if ( response.GetStatus() != ideoengine::message::Response::Status::Successful ) {
            LOG(LOG_ERROR) << "Can't join president.";
            LOG(LOG_ERROR) << "Exit with failure.";

            exit(EXIT_FAILURE);
        }
        else {
            LOG(LOG_INFO) << "Join successfully";
        }

        manager.StartListen();
    });
}

#ifdef ENABLE_MULTILANG_JAVA
static void StartJVM(const ideoengine::util::Configuration& configuration)
{
    using ideoengine::java::VirtualMachine;

    VirtualMachine* vm = new VirtualMachine();
    VirtualMachine::SetDefault(vm);
    vm->SetVersion(JNI_VERSION_1_8);
    vm->AddClassPath(configuration.GetProperty(ideoengine::CONF_KEY_JAVA_CLASSPATH));
    LOG(LOG_DEBUG) << "Java classpath: " <<
                      configuration.GetProperty(ideoengine::CONF_KEY_JAVA_CLASSPATH);

    vm->Start();
}
#endif // ENABLE_MULTILANG_JAVA

static void ProcessSignal(int signalNumber) {
    LOG(LOG_ERROR) << "Receive signal number: " << signalNumber;
    LOG(LOG_ERROR) << "Exit";
    exit(0);
}

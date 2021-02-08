

#include "ideoengine/service/President.h"
#ifdef ENABLE_MULTILANG_JAVA
#include "ideoengine/multilang/java/VirtualMachine.h"
#include "ideoengine/multilang/java/String.h"
#endif // ENABLE_MULTILANG_JAVA
#include "ideoengine/topology/TopologyLoader.h"
#include "ideoengine/util/Configuration.h"
#include "ideoengine/base/Constants.h"

#include <iostream>
#include <string>
#include <csignal>
#include <thread>

using namespace std;

void StartPresident(const std::string& configFileName);
#ifdef ENABLE_MULTILANG_JAVA
static void StartJVM(const ideoengine::util::Configuration& configuration);
#endif // ENABLE_MULTILANG_JAVA
static void ProcessSignal(int signalNumber);

int main(int argc, char* argv[])
{
    if ( argc < 2 ) {
        return EXIT_FAILURE;
    }

    StartPresident(argv[1]);

    return EXIT_SUCCESS;
}

void StartPresident(const std::string& configFileName) {
    ideoengine::util::Configuration presidentConfigratuion;
    presidentConfigratuion.Parse(configFileName);

#ifdef ENABLE_MULTILANG_JAVA
    if ( presidentConfigratuion.GetBooleanProperty(ideoengine::CONF_KEY_ENABLE_JAVA) ) {
        StartJVM(presidentConfigratuion);
    }
#endif // ENABLE_MULTILANG_JAVA

    signal(SIGINT, ProcessSignal);

    ideoengine::service::President president(presidentConfigratuion);
    president.StartListen();
}

#ifdef ENABLE_MULTILANG_JAVA
static void StartJVM(const ideoengine::util::Configuration& configuration)
{
    using ideoengine::java::VirtualMachine;
    using ideoengine::java::String;

    VirtualMachine* vm = new VirtualMachine;
    VirtualMachine::SetDefault(vm);
    vm->SetVersion(JNI_VERSION_1_8);
    vm->AddClassPath(configuration.GetProperty(ideoengine::CONF_KEY_JAVA_CLASSPATH));
    LOG(LOG_DEBUG) << "Java classpath: " <<
                      configuration.GetProperty(ideoengine::CONF_KEY_JAVA_CLASSPATH);

    vm->Start();

    LOG(LOG_DEBUG) << "Current thread id: " <<std::this_thread::get_id();

    signal(SIGINT, ProcessSignal);
}
#endif // ENABLE_MULTILANG_JAVA

static void ProcessSignal(int signalNumber) {
    LOG(LOG_ERROR) << "Receive signal number: " << signalNumber;
    LOG(LOG_ERROR) << "Exit";
    exit(0);
}

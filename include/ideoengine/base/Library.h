#pragma once

#include "logging/Logging.h"

#include <string>
#include <iostream>

#ifdef WIN32

#include <Windows.h>

typedef HMODULE LibraryHandle;

inline LibraryHandle IdeoengineLibraryLoad(const std::string& name) {
    std::string path = name + ".dll";
    return LoadLibraryA(path.c_str());
}

#define IdeoengineLibraryFree FreeLibrary

inline DWORD IdeoengineGetLibraryError() {
    return GetLastError();
}

#else

#include <dlfcn.h>

typedef void* LibraryHandle;
inline LibraryHandle IdeoengineLibraryLoad(const std::string& name) {
    std::string path("lib");
    path += name + ".so";
    LibraryHandle handle = dlopen(path.c_str(), RTLD_NOW);
    if ( !handle ) {
        LOG(LOG_ERROR) << dlerror();
        exit(EXIT_FAILURE);
    }

    return handle;
}
#define IdeoengineLibraryFree dlclose

#define IdeoengineGetLibraryError() dlerror()

#endif

#ifdef __cplusplus
#include <string>

template <class Function>
Function IdeoengineLibraryGetSymbol(LibraryHandle libraryHandle, const std::string& libraryName) {
#ifdef WIN32
    return reinterpret_cast<Function>(GetProcAddress(libraryHandle, libraryName.c_str()));
#else
    return reinterpret_cast<Function>(dlsym(libraryHandle, libraryName.c_str()));
#endif
}

std::string GetLibraryPath();

#endif // __cplusplus

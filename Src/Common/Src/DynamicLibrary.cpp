#include "Common/DynamicLibrary.h"

#include <filesystem>
#include <iostream>

#include <dlfcn.h>

using namespace Common;

// TODO: 需要设计一下插件加载路径
std::string GetPlatformSpecificLibraryName(const std::string& name)
{
    std::string filename = name;

#ifndef _WIN32
    if (filename.find("lib") == std::string::npos) {
        filename = "lib" + filename;
    }
#endif

#if (defined _WIN32)
    static const std::string ext = "dll";
#elif defined(__APPLE__)
    static const std::string ext = "dylib";
#else
    static const std::string ext
        = "so";
#endif

    if (filename.substr(filename.find_last_of('.') + 1) != ext) {
        filename.append(".").append(ext);
    }

    return filename;
}

DynamicLibrary::DynamicLibrary(const std::string& lib)
{
    std::string path = lib;
#if DEBUG
    path = BIN_PATH "/" + lib;
#endif
    m_handle = dlopen(path.c_str(), RTLD_NOW);
}

DynamicLibrary::~DynamicLibrary()
{
    dlclose(m_handle);
}

void* DynamicLibrary::GetSymbol(const std::string& symbol)
{
    return dlsym(m_handle, symbol.c_str());
}

DynamicLibrary* DynamicLibraryManager::Load(const std::string& name)
{
    const std::string& libPath = GetPlatformSpecificLibraryName(name);
    if (!m_libraries.contains(name)) {
        m_libraries[name] = std::make_unique<DynamicLibrary>(libPath);
    }
    return m_libraries[name].get();
}

void DynamicLibraryManager::Unload(const std::string& name)
{
    m_libraries.erase(name);
}

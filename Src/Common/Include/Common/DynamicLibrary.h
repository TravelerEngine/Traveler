#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#if PLATFORM_WINDOWS
#include <Windows.h>
#define DYNAMIC_LIB_HANDLE               HINSTANCE
#define DYNAMIC_LIB_LOAD(lib, tag)       LoadLibraryEx(lib, nullptr, 0)
#define DYNAMIC_LIB_GET_SYMBOL(lib, sym) GetProcAddress(lib, sym)
#define DYNAMIC_LIB_UNLOAD(lib)          FreeLibrary(lib)
#else
#include <dlfcn.h>
#define DYNAMIC_LIB_HANDLE               void*
#define DYNAMIC_LIB_LOAD(lib, tag)       dlopen(lib, tag)
#define DYNAMIC_LIB_GET_SYMBOL(lib, sym) dlsym(lib, sym)
#define DYNAMIC_LIB_UNLOAD(lib)          dlclose(lib)
#endif

namespace Common {

class DynamicLibrary {
public:
  explicit DynamicLibrary(const std::string &lib);
  virtual ~DynamicLibrary();
  inline DYNAMIC_LIB_HANDLE GetHandle() const { return m_handle; }
  void *GetSymbol(const std::string &name);

private:
  DYNAMIC_LIB_HANDLE m_handle = nullptr;
};

class DynamicLibraryManager {
  std::unordered_map<std::string, std::unique_ptr<DynamicLibrary>> m_libraries;

public:
  static DynamicLibraryManager &Singleton() {
    static DynamicLibraryManager instance;
    return instance;
  }

  DynamicLibrary *Load(const std::string &name);
  void Unload(const std::string &name);
};
} // namespace Common

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <dlfcn.h>

namespace Common {

class DynamicLibrary {
public:
  explicit DynamicLibrary(const std::string &lib);
  virtual ~DynamicLibrary();
  inline void *GetHandle() const { return m_handle; }
  void *GetSymbol(const std::string &name);

private:
  void *m_handle = nullptr;
};

class DynamicLibraryManager {
  std::unordered_map<std::string, std::unique_ptr<DynamicLibrary>> m_libraries;

public:
  static DynamicLibraryManager &Singleton() {
    static DynamicLibraryManager instance;
    return instance;
  }

  ~DynamicLibraryManager() {
    for (auto &&iter : m_libraries) {
      dlclose(iter.second->GetHandle());
    }
  }

  DynamicLibrary *Load(const std::string &name);
  void Unload(const std::string &name);
};
} // namespace Common

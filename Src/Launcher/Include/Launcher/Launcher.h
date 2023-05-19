#pragma once

#include <memory>

namespace Main {
    class LauncherPrivate;
    class Launcher {
        std::shared_ptr<LauncherPrivate> m_private;

    public:
        explicit Launcher(int argc, char* argv[]);
        ~Launcher();

        int Exec();
    };
} // namespace Main

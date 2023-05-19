#include "Launcher/Launcher.h"

int main(int argc, char* argv[])
{
    Main::Launcher launcher(argc, argv);
    return launcher.Exec();
}

#include <RHI/Common.h>
#include <RHI/Instance.h>
#include <string>

#include <boost/program_options.hpp>

#include <iostream>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  po::options_description options("options");
  options.add_options()("help", "help")("rhi", po::value<std::string>(),
                                        "RHI Type");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, options), vm);
  po::notify(vm);

  if (vm.count("help") != 0) {
    std::cout << options << std::endl;
    return 1;
  }

  if (vm.count("RHI") != 0) {
    std::cout << "RHI Type is not set" << std::endl;
    return -1;
  }

  std::string RHI{vm["rhi"].as<std::string>()};

  if (RHI == "auto") {
#if defined(__APPLE__)
    RHI = "Vulkan";
#else
    // TODO: add windows dx12 support
    RHI = "Vulkan";
#endif
  }

  std::cout << "Init RHI: " << RHI << std::endl;

  // TODO: 改成加载全部插件，使用插件类型判断 RHI 是否正确。
  RHI::Instance *instance = RHI::Instance::CreateByType(RHI);
  std::cout << instance << std::endl;
  std::cout << RHI::ToString(instance->GetRHIType()) << std::endl;

  return 0;
}

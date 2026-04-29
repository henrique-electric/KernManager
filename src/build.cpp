#include <core.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>

// clang-format off
extern "C" void build(const struct kernel_version *kver) {
    std::string version = kver->str_version;;
    std::string user_home = getenv("HOME");
    std::string linux_path = "./linux-" + std::to_string(kver->major) + "." + std::to_string(kver->middle) + "." + std::to_string(kver->minor);
    int minor = kver->minor;

    if (kver->minor == MINOR_VERSION_NOT_SPECIFIED || kver->minor == 0) {
      version = std::to_string(kver->major) + std::to_string(kver->middle);
      minor = 0;
      linux_path = "./linux-" + std::to_string(kver->major) + "." + std::to_string(kver->middle);
      std::cout << linux_path;
    } 
        
    
    int res = chdir(linux_path.c_str());
    
    if (res == -1) {
      std::cout << "Error on going to linux source tree\n";
      exit(EXIT_FAILURE);
    }
    
    if (system("mkdir build && cp /usr/local/certs/MOK_CERT.pem certs") == -1) {
      std::cout << "Error creating the build directory and copying the secureboot cert\n";
      exit(EXIT_FAILURE);
    }
    
    std::string cmd = "cp /usr/local/kernel_configs/" + std::to_string(kver->major) + "." + std::to_string(kver->middle) + "." + std::to_string(minor) + " build/.config";
    if (system(cmd.c_str()) == -1) {
      std::cout << "Error copying the build config for the provided version\n";
      exit(EXIT_FAILURE);
    }
    

    if (system("make O=build -j$(nproc) && make O=build modules_prepare && sudo make O=build modules_install && sudo cp build/arch/x86/boot/bzImage /boot/linux-custom") == -1) {
      std::cout << "Error building the kernel and installing\n";
      exit(EXIT_FAILURE);
    }
   
    if (kver->minor == MINOR_VERSION_NOT_SPECIFIED)
      cmd = "sudo rm /lib/modules/" + std::to_string(kver->major) + "." + std::to_string(kver->middle) + "/build";
    else
      cmd = "sudo rm /lib/modules/" + std::to_string(kver->major) + "." + std::to_string(kver->middle) + "." + std::to_string(kver->minor) + "/build";
    
    if (system(cmd.c_str()) == -1) {
      std::cout << "Error removing modules build dir symlink\n";
      exit(EXIT_FAILURE);
    }
    
    if(system("pushd build && make clean") == -1) {
      std::cout << "Error cleaning build directory\n";
      exit(EXIT_FAILURE);
    }
   
    if(minor == 0)
      cmd = "sudo mv build /lib/modules/" + std::to_string(kver->major) + "." + std::to_string(kver->middle); 
    else
      cmd = "sudo mv build /lib/modules/" + std::to_string(kver->major) + "." + std::to_string(kver->middle) + "." + std::to_string(kver->minor);

}

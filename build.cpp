#include <core.h>
#include <string>
#include <filesystem>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>
#include <iostream>

extern "C" void build(const struct kernel_version *kver) {
    std::string version = kver->str_version;;
    std::string user_home = getenv("HOME");
    std::string linux_path;

    if (kver->minor == MINOR_VERSION_NOT_SPECIFIED) {
        linux_path = user_home + "/" + version + ".0";
        version = version + ".0";
        
    }
        
    else
        linux_path = user_home + "/" + kver->str_version;
    
    int res = chdir(linux_path.c_str());
    
    if (res == -1)
        std::cout << "Error on going to linux source tree\n";
    
    system("mkdir build && cp /usr/local/certs/MOK_CERT.pem certs");
    
    std::string cmd = "cp /usr/local/kernel_configs/" + version + "build/.config/";
    system(cmd.c_str());
    
    system("make O=build -j$(nproc) && make O=build modules_prepare && make O=build modules_install && sudo cp build/arch/x86/boot/bzImage /boot/linux-custom");
    
    cmd = "sudo rm /lib/modules/" + version + "/build";
    system(cmd.c_str());
    
    system("make O=build clean");
    
    cmd = "sudo mv build " + version + "/build";
    
}

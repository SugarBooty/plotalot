#include "Config.hpp"
#include "plotJob.hpp"

#include <iostream>

int main() {
    std::cout << "2" << std::endl;

    Config Config("config.txt");
    Config::configMap localMap = Config.getMappedConfig();

    std::cout << "2" << std::endl;

    // for ( auto [key, valVec] : localMap ){
    //     for ( auto val : valVec){
    //     std::cout << "Key: " << key << " Val: " << val << std::endl;

    //     }
    // }

    Config.writeTest("test", "test.test");
    return 0;
}
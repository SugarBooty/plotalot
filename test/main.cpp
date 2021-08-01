

#include <iostream>
#include <filesystem>
#include <ctime>

int main() {

    std::cout << std::time(nullptr) << std::endl;

    //Config Config("config.txt");
    //Config::configMap localMap = Config.getMappedConfig();
    //if (!localMap.empty())
    //    std::cout << "Config passed" << std::endl;

    //std::unordered_map<std::string, std::string> mapbaby = logParser::parsePlotLog("samplePlotOutput.log");
    //for ( auto [key, val] : mapbaby ){
    //    std::cout << "Key: " << std::setw(20) << key << " | Val: " << val << std::endl;

        
    //}

    // Config.writeTest("test", "test.test");
    return 0;
}
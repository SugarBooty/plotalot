
#include "logParser.hpp"

#include <iostream>
#include <filesystem>

int main() {

    // Config Config("config.txt");
    // Config::configMap localMap = Config.getMappedConfig();

    std::unordered_map<std::string, std::string> mapbaby = logParser::parsePlotLog("samplePlotOutput.log");
    for ( auto [key, val] : mapbaby ){
        std::cout << "Key: " << std::setw(20) << key << " | Val: " << val << std::endl;

        
    }

    // Config.writeTest("test", "test.test");
    return 0;
}
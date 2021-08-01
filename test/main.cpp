#include "../headers/logParser.hpp"
#include "../headers/SaveStats.hpp"

#include <iostream>
#include <filesystem>
#include <ctime>
#include <unordered_map>
#include <map>

int main() {

    std::cout << std::time(nullptr) << std::endl;

    //Config Config("config.txt");
    //Config::configMap localMap = Config.getMappedConfig();
    //if (!localMap.empty())
    //    std::cout << "Config passed" << std::endl;
    LogParser parser = LogParser();
    parser.setPath("/home/sugar/Documents/code/plotalotv2/test/samplePlotOutput.log");

    std::unordered_map<std::string, std::string> mapbaby = parser.parsePlotLog();
    for ( auto [key, val] : mapbaby ){
       std::cout << "Key: " << std::setw(20) << key << " | Val: " << val << std::endl;
    }

    SaveStats statistics = SaveStats("/home/sugar/Documents/code/plotalotv2/test/sampleStatistics.log", mapbaby);


    std::cout << mapbaby.size() << std::endl;



    // Config.writeTest("test", "test.test");
    return 0;
}
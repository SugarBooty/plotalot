#include "../headers/logParser.hpp"
#include "../headers/SaveStats.hpp"
#include "../headers/JobMan.hpp"

#include <iostream>
#include <filesystem>
#include <ctime>
#include <unordered_map>
#include <map>

namespace fs = std::filesystem;

int main() {

    std::cout << std::time(nullptr) << std::endl;

    //Config Config("config.txt");
    //Config::configMap localMap = Config.getMappedConfig();
    //if (!localMap.empty())
    //    std::cout << "Config passed" << std::endl;

    // fs::path logFile("/home/sugar/Documents/code/plotalotv2/test/samplePlotOutput.log");

    // LogParser parser = LogParser();
    // parser.setPath(logFile);

    // std::unordered_map<std::string, std::string> mapbaby = parser.parsePlotLog();
    // for ( auto [key, val] : mapbaby ){
    //    std::cout << "Key: " << std::setw(20) << key << " | Val: " << val << std::endl;
    // }

    // fs::path statFile("/home/sugar/Documents/code/plotalotv2/test");

    // statFile /= "sampleStatistics.log";

    // SaveStats statistics = SaveStats( mapbaby, statFile );


    // std::cout << mapbaby.size() << std::endl;

    JobMan manager;

    manager.startNewJob();




    // Config.writeTest("test", "test.test");
    return 0;
}
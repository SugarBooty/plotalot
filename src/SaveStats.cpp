#include "../headers/SaveStats.hpp"

#include <map>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>


SaveStats::SaveStats(const std::string& path, const infoMap& map) {
    appendToFile(map, path);
}

bool SaveStats::appendToFile(const infoMap& map, const std::string& path) {
    std::ofstream statsFile;
    statsFile.open(path, std::ios::app);
    if ( statsFile ){
        std::string valueString;

        statsFile << formatMap(map) << std::endl;
        
        statsFile.close();
        return true;
    } else {
        std::cout << "stats file could not be appended to " << path << std::endl;
        return false;
    }
}

std::string SaveStats::formatMap(infoMap map) const {
    // this returns a formatted CSV style thingy
    // KEY=VAL,KEY=VAL,KEY=VAL\n
    std::string outputLine;
    for ( auto [key, value] : map )
        outputLine += key + "=" + value + ",";
    return outputLine;
}
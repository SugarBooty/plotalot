#include "../headers/SaveStats.hpp"

#include <map>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

SaveStats::SaveStats(const infoMap& map, const fs::path& path) {
    std::ofstream statsFile;
    statsFile.open(path, std::ios::app);
    if ( statsFile ){
        std::string valueString;

        statsFile << formatMap(map) << std::endl;
        
        statsFile.close();
    } else {
        std::cout << "stats file could not be appended to " << path << std::endl;
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
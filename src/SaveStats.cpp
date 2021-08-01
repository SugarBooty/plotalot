#include "../headers/SaveStats.hpp"

#include <map>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>


std::string SaveStats::formatMap(const infoMap& map) const {
    // this returns a formatted CSV style thingy
    // KEY=VAL,KEY=VAL,KEY=VAL\n
    std::string outputLine;
    for ( auto [key, value] : map )
        outputLine += key + "=" + value + ",";
    return outputLine + "\n";
}
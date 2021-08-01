#pragma once

#include <map>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

class SaveStats {
    public:
        typedef std::unordered_map<std::string, std::string> infoMap;
        // saves data to the stats file upon a completed plot
        SaveStats(const std::string& path, const infoMap& map);

    private:
        // appends to the stats file
        bool appendToFile(const infoMap& map, const std::string& path);
        // returns a string of formatted map data
        std::string formatMap(infoMap) const;
};

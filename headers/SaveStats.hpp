#pragma once

#include <map>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

class SaveStats {
    public:
        typedef std::unordered_map<std::string, std::string> infoMap;
        // appends to the stats file
        SaveStats(const infoMap& map, const fs::path& path);
    private:
        // returns a string of formatted map data
        std::string formatMap(infoMap) const;
};

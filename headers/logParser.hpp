#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <optional>
#include <unordered_map>
#include <map>
#include <sstream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class LogParser {
    public:
        typedef std::optional< std::pair<std::string, std::string> > optionalLineInfo;
        typedef std::unordered_map<std::string, std::string> infoMap;

        void setPath(const fs::path& path);

        infoMap parsePlotLog();

    private:
        fs::path logPath;
        optionalLineInfo parseLine(const std::string& line);

};

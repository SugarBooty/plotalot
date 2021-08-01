#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <optional>
#include <unordered_map>
#include <map>
#include <sstream>
#include <vector>

class LogParser {
    public:
        typedef std::optional< std::pair<std::string, std::string> > optionalLineInfo;
        typedef std::map<std::string, std::string> infoMap;

        void setPath(const std::string& path);

        infoMap parsePlotLog();

    private:
        std::string logPath;
        optionalLineInfo parseLine(const std::string& line);

};

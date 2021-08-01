#include <map>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

class SaveStats {
    public:
        typedef std::map<std::string, std::string> infoMap;
        // saves data to the stats file upon a completed plot
        SaveStats(std::string path, infoMap map);

    private:
        // appends to the stats file
        bool appendToFile(infoMap map, std::string path);
        // returns a string of formatted map data
        std::string formatMap(infoMap);
};

SaveStats::SaveStats(std::string path, infoMap map) {
    appendToFile(map, path);
}

bool SaveStats::appendToFile(infoMap map, std::string path) {
    std::ofstream statsFile;
    statsFile.open(path, std::ios::app);
    if ( !statsFile ){
        std::string valueString;

        statsFile << formatMap(map) << std::endl;
        
        statsFile.close();
        return true;
    } else {
        std::cout << "stats file could not be appended to " << path << std::endl;
        return false;
    }
}

std::string SaveStats::formatMap(infoMap map) {
    // this returns a formatted CSV style thingy
    // KEY=VAL,KEY=VAL,KEY=VAL\n
    std::string outputLine;
    for ( auto [key, value] : map )
        outputLine += key + "=" + value + ",";
    return outputLine + "\n";
}
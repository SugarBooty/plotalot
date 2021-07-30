

#include <string>
#include <fstream>
#include <optional>
#include <unordered_map>

namespace logParser {
    typedef std::optional< std::pair<std::string, std::string> > optionalLineInfo;


    struct logInfo {
        int currentPhase;                       
        int currentTable;
        int phase1Duration;
        int phase2Duration;
        int phase3Duration;
        int phase4Duration;
        int totalDuration;
        int movePlotDuration;
    };

    std::unordered_map<std::string, std::string> durationInfo;

// TODO figure out how to add functtionality to make this add the current latest state information
// maybe just update it after every line
    struct logInfo parsePlotLog(std::string path) {
        std::ifstream logFile (path);
        std::string line;
        logInfo returnValues;
        if ( logFile.is_open() ) {
            while ( std::getline (logFile, line) ) {
                // TODO add line by line parse function (kinda done)
                optionalLineInfo lineInfo = parseLine(line);
                // TODO add all the if statements to make this put the right data in the struct
                if ( lineInfo ) {
                    if ( lineInfo->first == "idfk man") {

                    }
                }
            }
            return returnValues;
        }
    }

// TODO add parsing functionality
// recieves line, spits out label and value
    optionalLineInfo parseLine(std::string line) {

    }

// I honestly dont know what I did this for 
    struct logEntry {
        std::string phase1;
        std::string phase2;
        std::string phase3;
        std::string phase4;
        std::string totalDur;
    };
    
}
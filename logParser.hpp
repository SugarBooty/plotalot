

#include <string>
#include <fstream>
#include <iostream>
#include <optional>
#include <unordered_map>
#include <sstream>
#include <vector>

namespace logParser {
    typedef std::optional< std::pair<std::string, std::string> > optionalLineInfo;
    typedef std::unordered_map<std::string, std::string> infoMap;


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


    infoMap parsePlotLog(std::string path) {
        std::ifstream logFile (path);
        std::string line;
        infoMap durationInfo;
        if ( logFile.is_open() ) {
            while ( std::getline (logFile, line) ) {
                optionalLineInfo lineInfo = parseLine(line);
                durationInfo[lineInfo->first] = lineInfo->second;
            }
            return durationInfo;
        }
    }


    optionalLineInfo parseLine(const std::string& line) {
        std::istringstream issLine(line);           // makes a string stream from the line
        std::vector<std::string> lineElements;      // initializes a vector of strings, this will be the string deliniated by spaces
        std::string lineElement;                    // the element that is assigned the value in the while loop
        while ( std::getline(issLine, lineElement, ' ') ) {
            lineElements.push_back(lineElement);
        }

        auto contains = [](std::string value, std::string key) {
            return value.find(key) != std::string::npos;
        };

        optionalLineInfo returnInfo;
        std::string descriptor;
        // phase 1 duration parsing
        // sample:
        // [P1] Table 1 took 16.3313 sec
        // [P1] Table 2 took 121.511 sec, found 4294997622 matches
        if ( contains(line, "[P1]") ) {
                descriptor = "p1_t" + lineElements[2] + "_dur";
                return std::make_pair( descriptor, lineElements[4] );
        }
        // phase 2 duration parsing
        // sample:
        // [P2] Table 7 scan took 14.5722 sec
        // [P2] Table 7 rewrite took 48.9663 sec, dropped 0 entries (0 %)
        if ( contains(line, "[P2]") ) {
            if ( contains(line, "scan") ) {
                descriptor = "p2_t" + lineElements[2] + "_scan_dur";
                return std::make_pair( descriptor, lineElements[5] );
            } else if ( contains(line, "rewrite") ) {
                descriptor = "p2_t" + lineElements[2] + "_rewrite_dur";
                return std::make_pair( descriptor, lineElements[5] );
            }
        }
        // phase 3 parsing
        // sample
        // [P3-1] Table 2 took 49.2539 sec, wrote 3429426169 right entries
        // [P3-2] Table 2 took 31.1873 sec, wrote 3429426169 left entries, 3429426169 final
        if ( contains(line, "[P3-") ) {
            if ( contains(line, "[P3-1]") ) {
                descriptor = "p3_t" + lineElements[2] + "_r_dur";
                return std::make_pair( descriptor, lineElements[4] );
            } else if ( contains(line, "[P3-2]") ) {
                descriptor = "p3_t" + lineElements[2] + "_l_dur";
                return std::make_pair( descriptor, lineElements[4] );
            }
        }
        // phase 4 parsing
        // sample
        // [P4] Starting to write C1 and C3 tables
        // [P4] Finished writing C1 and C3 tables
        // [P4] Writing C2 table
        // [P4] Finished writing C2 table
        if ( contains(line, "[P4]") ) {
            if ( contains(line, "Starting to write C1 and C3 tables") )
                return std::make_pair( "p4_t1", "done" );
            if ( contains(line, "Finished writing C1 and C3 tables") )
                return std::make_pair( "p4_t2", "done" );
            if ( contains(line, "Finished writing C2 table") )
                return std::make_pair( "p4_t4", "done" );
            if ( contains(line, "Writing C2 table") )
                return std::make_pair( "p4_t3", "done" );
        }
        // total phase duration parsing
        // sample
        // Phase 1 took 896.998 sec
        // Phase 4 took 75.1327 sec, final plot size is 108835900691 bytes
        if ( contains(line, "Phase ") ) {
            if ( contains(line, "Phase 1") )
                return std::make_pair( "phase1duration", lineElements[3] );
            else if ( contains(line, "Phase 2") )
                return std::make_pair( "phase2duration", lineElements[3] );
            else if ( contains(line, "Phase 3") )
                return std::make_pair( "phase3duration", lineElements[3] );
            else if ( contains(line, "Phase 4") )
                return std::make_pair( "phase4duration", lineElements[3] );
        }
    }
}
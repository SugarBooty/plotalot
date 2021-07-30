#include "jobMan.hpp"
#include "Config.hpp"
#include "global_config.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <filesystem>
#include <algorithm>
#include <iostream>

// TODO add statistics gathering functionality
// TODO add plot log reader class

namespace fs = std::filesystem;

JobMan::JobMan() {

}

void JobMan::_initRunningPlotsOnStart() {
    // TODO add functionality to tell if plots are dead or running

}

bool JobMan::startNewJob(bool restore = false) {
    // starts new plot job, appends the object to the running job vector, and makes a state file in the temp directory its plotting in
    individualConfig jobConfig = generateIndividualConfig();
    runningPlotJobVector.push_back( PlotJob(jobConfig) );
    std::string path = jobConfig[config::TEMP_DIR] + jobConfig["jobID"] + ".pltjob";
    if (config.createFileFromMap( jobConfig, path )) { // TODO use the PlotJob getter function to get config value map, as the construction of the object adds values to it
        std::cout << "Started new plot job, state file: " << path << std::endl;
    } else {
        std::cout << "Started new plot job, could not create state file. Check permissions!" << std::endl;
    }
    return true;
}

bool JobMan::restoreAllJobs() {
    for ( std::string stateFilePath : findAllPlotJobStateFiles() ) {
        individualConfig extrapolatedConfig = config.getMappedConfig(stateFilePath);
        runningPlotJobVector.push_back( PlotJob(extrapolatedConfig, true) );
        std::cout << "Restored running plot job state from file: " << stateFilePath << std::endl;
    }
}

JobMan::individualConfig JobMan::generateIndividualConfig() {
    std::string optimalTempDrive = getOptimalTempDrive();
    std::optional<std::string> optionalOptimalDestDrive = getOptimalDestDrive();
    std::string optimalDestDrive;
    if ( optionalOptimalDestDrive )
        optimalDestDrive = optionalOptimalDestDrive.value();
    else {
        // no optimal drive found, this means theres not enough room on any of them
        // TODO add handling for no suitable dest drives
    }

    // TODO include new needec config values in individual config: "jobStartTime"

    individualConfig outputConfig;
    wholeConfig wholeConfig = config.getMappedConfig();

    wholeConfig.erase(config::TEMP_DIR);
    wholeConfig.erase(config::DEST_DIR);

    for (auto& [key,value] : wholeConfig)
        outputConfig[key] = value[0];

    outputConfig[config::TEMP_DIR] = optimalTempDrive;
    outputConfig[config::DEST_DIR] = optimalDestDrive;

    return outputConfig;
}

std::optional<std::string> JobMan::getOptimalDestDrive() {
    std::vector<std::string> destDriveVector = config.getValues(config::DEST_DIR);
    std::map<std::string, fs::space_info> dirMap;
    for (auto item : destDriveVector)
        dirMap[item] = fs::space( fs::path(item) );

    std::vector<individualConfig> runningConfigVector = getPlotJobConfigs();

    std::vector<std::string> runningDestDir;
    for (auto item : runningConfigVector)
        runningDestDir.push_back(config.getValueFromMap(item, config::DEST_DIR));

    // I have a map of the config directory space info and a vector of the running plot destination directories
    // I need to formulate the estimated space once they finish and determine whether or not theres a suitable drive to plot to
    std::unordered_map< std::string, std::pair<bool, int> > projectedFreeSpace;
    for (auto [dir_name, dir_info] : dirMap) {
        int occurrence = std::count(runningDestDir.begin(), runningDestDir.end(), dir_name);
        long available = dir_info.available / 1000000000;
        long capacity  = dir_info.capacity  / 1000000000;
        long projectedAvailable = available + ( 103 * (occurrence + 1) );
        int projectedUsagePercentage = projectedAvailable / capacity;

        bool enoughRoom = projectedAvailable <= capacity;
        std::pair<bool, int> output;

        output.first = enoughRoom;
        output.second = projectedUsagePercentage;

        projectedFreeSpace[dir_name] = output;
    }
    // now I have a map of the drives specified in the config, their percentage full, and if they have enough room to start a plot to
    // I need to get the smallest percentage value of the map and return it if theres enough room

    std::pair<std::string, int> optimalDrive;
    optimalDrive.second = 100;
    for ( auto [dir_name, space_pair] : projectedFreeSpace) {
        if (space_pair.first) { // if enoughRoom
            // find drive with minimum percentage used
            if (space_pair.second < optimalDrive.second) {
                optimalDrive.first = dir_name;
                optimalDrive.second = space_pair.second;
            }
        }
    }

    if (optimalDrive.second == 100)
        return std::nullopt;
    else
        return optimalDrive.first;
}

std::string JobMan::getOptimalTempDrive() {
    std::vector<std::string> tempDriveVector = config.getValues(config::TEMP_DIR);
    std::vector<individualConfig> runningConfigVector = getPlotJobConfigs();
    std::unordered_map<std::string, int> runningTempDriveOccurrence;
    std::vector<std::string> runningTempDriveVector;
    for (auto item : runningConfigVector)
        runningTempDriveVector.push_back(item[config::TEMP_DIR]);
    for (auto item : tempDriveVector) {
        int occurrence = count(runningTempDriveVector.begin(), runningTempDriveVector.end(), item);
        runningTempDriveOccurrence[item] = occurrence;
    }

    std::pair<std::string, int> optimalDrive;
    optimalDrive.second = 1000;
    for (auto item : runningTempDriveOccurrence) {
        if ( item.second < optimalDrive.second )
            optimalDrive = item;
    }

    return optimalDrive.first;
}

std::vector<JobMan::individualConfig> JobMan::getPlotJobConfigs() {
    std::vector<individualConfig> allPlotJobConfigVector;
    for ( auto plotJobObject : runningPlotJobVector ) {
        allPlotJobConfigVector.push_back( plotJobObject.getConfigMap() );
    }
    return allPlotJobConfigVector;
}

std::vector<std::string> JobMan::findAllPlotJobStateFiles() {
    std::vector<std::string> plotJobStatePaths;
    for ( std::string tempDir : config.getMappedConfig()[config::TEMP_DIR] ) {
        for ( auto file : fs::directory_iterator(tempDir) ) {
            if (file.path().extension() == ".pltjob") {
                plotJobStatePaths.push_back(file.path().string());
            }
        }
    }
    return plotJobStatePaths;
}



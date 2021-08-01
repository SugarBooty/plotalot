#include "../headers/PlotJob.hpp"
#include "../headers/global_config.hpp"
#include "../headers/logParser.hpp"

#include <string>
#include <stdexcept>
#include <memory>
#include <ctime>


// public methods

PlotJob::PlotJob(configMap config, bool restore) {
    jobConfig = config;
    jobRestore = restore;
}

void PlotJob::begin() {
    if ( !jobRestore ) {
        jobConfig["jobStartTime"] = std::time(nullptr);
        runCommand( buildCommand() );
        parsePlotLog();
    } else {
        parser.setPath(getVal("localLogFile"));
        parsePlotLog();
    }

}

void PlotJob::suspend() {

}

void PlotJob::resume() {

}

void PlotJob::kill() {

}

PlotJob::configMap PlotJob::getConfigMap() {
    return jobConfig;
}

// TODO add start time into the stats returned

bool PlotJob::parsePlotLog() {
    logInfo = parser.parsePlotLog();
    jobConfig["PID"] = logInfo["PID"];
    jobConfig["plotname"] = logInfo["plotname"];
    jobConfig["currentphase"] = logInfo["laststate"];
    return true;
}

// TODO add object killing function

// private methods

std::string PlotJob::buildCommand() {
    std::string command;
    command += getVal(config::CHIA_COMMAND);
    command += " -n 1"; // sets the amount of plots generated to 1 to allow proper functionality of this program
    command += " -r " + getVal(config::THREADS);
    command += " -u " + getVal(config::BUCKETS);
    command += " -t " + getVal(config::TEMP_DIR);
    command += " -d " + getVal(config::DEST_DIR);
    command += " -c " + getVal(config::POOL_CONTRACT_ADDRESS);
    command += " -f " + getVal(config::FARMER_PUBLIC_KEY);
    if ( getVal(config::THREAD_MULTIPLIER) != "false" )
        command += " -K " + getVal(config::THREAD_MULTIPLIER);
    if ( getVal(config::BUCKETS_3_4) != "false" )
        command += " -v " + getVal(config::BUCKETS_3_4);
    if ( getVal(config::TEMP_RAM_DIR) != "false" )
        command += " -2 " + getVal(config::TEMP_RAM_DIR);
    
    std::string logFile = getVal("jobStartTime") + ".log";

    // makes the output of the command go to the specified file, located where the command was run from
    command += " > " + logFile;

    parser.setPath(logFile);

    jobConfig["localLogFile"] = logFile;
    jobConfig["localPlottingCommand"] = command;
    return command;
}

bool PlotJob::runCommand(const std::string& command) {
    // TODO implement starting the command (kinda done?)

    std::array<char, 512> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    std::cout << result << std::endl;

    return 0;
}


std::string PlotJob::getVal(const std::string& key){
    if ( jobConfig.find(key) != jobConfig.end() )
        return jobConfig[key];
    else
        throw(std::invalid_argument("No key called " + key + " found in local config. Something is most likely wrong here."));
}
#include "../headers/PlotJob.hpp"
#include "../headers/global_config.hpp"
#include "../headers/logParser.hpp"

#include <string>
#include <stdexcept>


// public methods

PlotJob::PlotJob(configMap config, bool restore) {
    jobConfig = config;
    jobRestore = restore;
}

void PlotJob::begin() {
    if ( !jobRestore ) {
        jobConfig["localPID"] = runCommand( buildCommand() );
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

bool PlotJob::parsePlotLog() {
    // TODO add parsing functionality
    // TODO add code to set config PID and other vars from log
}

// TODO add vars to store phase length info
// TODO add setter functions for current phase and pahase length info
// TODO add vars for total durations
// TODO add object killing function
// TODO figure out how to store statistics to persist if plotalot dies and can be restared with plot jobs restored

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

long PlotJob::runCommand(std::string command) {

    // TODO
    return 0;
}


std::string PlotJob::getVal(const std::string& key){
    if ( jobConfig.find(key) != jobConfig.end() )
        return jobConfig[key];
    else
        throw(std::invalid_argument("No key called " + key + " found in local config. Something is most likely wrong here."));
}
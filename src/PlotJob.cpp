#include "../headers/PlotJob.hpp"
#include "../headers/global_config.hpp"
#include "../headers/logParser.hpp"

#include <string>
#include <stdexcept>
#include <memory>
#include <ctime>
#include "/usr/include/unistd.h"
#include <thread>
#include <pthread.h>
#include <sys/types.h>
#include <csignal>


// public methods

PlotJob::PlotJob(configMap& config, bool restore) {
    jobConfig = config;
    jobRestore = restore;
    begin();
}

void PlotJob::begin() {
    if ( !jobRestore ) {
        jobConfig["jobStartTime"] = std::to_string( std::time(nullptr) );
        std::cout << "In PlotJob!" << std::endl; //FIXME dev code
        // runCommand( buildCommand() );
        runCommand();
        std::cout << "Ran command!" << std::endl;
        sleep(1);
        parsePlotLog();
        std::cout << "Parsed log!" << std::endl;
    } else {
        // TODO get absolute path for this
        parser.setPath(getVal("localLogFileName"));
        parsePlotLog();
    }

}

void launchTheThing() {
    
}

void PlotJob::suspend() {

}

void PlotJob::resume() {

}

void PlotJob::killPlot() {

}

PlotJob::configMap PlotJob::getConfigMap() {
    return jobConfig;
}

// TODO add start time into the stats returned

bool PlotJob::parsePlotLog() {
    logInfo = parser.parsePlotLog();
    for ( auto [logKey, logVal] : logInfo)
        std::cout << "logparser key: " << std::setw(20) << logKey << " | val: " << logVal << std::endl;
    jobConfig["PID"] = logInfo["PID"];
    jobConfig["plotname"] = logInfo["plotname"];
    jobConfig["currentphase"] = logInfo["laststate"];
    return true;
}

// TODO add object killing function

// private methods

std::string PlotJob::buildCommand() {
    std::string command;
    std::cout << "Building Command" << std::endl;
    // command += getVal(config::CHIA_COMMAND);
    // command += " -n 1"; // sets the amount of plots generated to 1 to allow proper functionality of this program
    // command += " -r " + getVal(config::THREADS);
    // command += " -u " + getVal(config::BUCKETS);
    // command += " -t " + getVal(config::TEMP_DIR);
    // command += " -d " + getVal(config::DEST_DIR);
    // command += " -c " + getVal(config::POOL_CONTRACT_ADDRESS);
    // command += " -f " + getVal(config::FARMER_PUBLIC_KEY);
    // if ( getVal(config::THREAD_MULTIPLIER) != "false" )
    //     command += " -K " + getVal(config::THREAD_MULTIPLIER);
    // if ( getVal(config::BUCKETS_3_4) != "false" )
    //     command += " -v " + getVal(config::BUCKETS_3_4);
    // if ( getVal(config::TEMP_RAM_DIR) != "false" )
    //     command += " -2 " + getVal(config::TEMP_RAM_DIR);

    // command += "/home/chia/Documents/plotalot_dev/test/plotOutputter.sh";
    command += fs::current_path().parent_path() / "test" / "plotOutputter.sh";
    
    // fs::path logFileName = "/home/chia/Documents/plotalot_dev/test/" + getVal("jobStartTime") + ".log";
    fs::path logFileName = fs::current_path().parent_path() / (getVal("jobStartTime") + "nev" + ".log"); //FIXME make this use the correct production path


    // makes the output of the command go to the specified file, located where the command was run from
    command += " > " + logFileName.string() + " & echo done";

    std::cout << "Command: " << command << std::endl;

    parser.setPath(logFileName);
    // TODO get absolute path for this

    jobConfig["localLogFileName"] = logFileName;
    jobConfig["localPlottingCommand"] = command;
    return command;
}

void PlotJob::forkStart() {
    pid_t child = fork();
    if ( child > 1 ) 
        sleep(1);
    else {
        runCommand();
        kill(child, SIGTERM);
    }
}

bool PlotJob::runCommand() {
    // TODO implement starting the command (kinda done?)
    std::string command = buildCommand();

    // std::array<char, 512> buffer;
    // std::string result;
    // std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    // if (!pipe) {
    //     throw std::runtime_error("popen() failed!");
    // }
    // while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    //     result += buffer.data();
    // }
    // std::cout << result << std::endl;

    // std::terminate();

    system(command.c_str());

    // execl(command);

    return 0;
}


std::string PlotJob::getVal(const std::string& key){
    if ( jobConfig.find(key) != jobConfig.end() )
        return jobConfig[key];
    else
        throw(std::invalid_argument("No key called " + key + " found in local config. Something is most likely wrong here."));
}
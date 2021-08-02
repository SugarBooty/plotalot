#pragma once

#include "Config.hpp"
#include "PlotJob.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <optional>

class JobMan {
    public:
        typedef std::unordered_map< std::string, std::vector<std::string> > wholeConfig;
        typedef std::unordered_map< std::string, std::string > individualConfig;

        JobMan();
        bool startNewJob(bool restore = false);

        bool restoreAllJobs();


    private:
        individualConfig lastJobGetConfig();

        // makes the individual config for the plot job, with the optimal dest and temp dir
        individualConfig generateIndividualConfig();
        // determines the temp drive for the next plot
        std::string getOptimalTempDrive();
        // determines the dest drive for the next plot, does not return anything if none have enough space
        std::optional<std::string> getOptimalDestDrive();
        
        //std::string getPlotJobObjectValue(const std::string& key);
        // returns the config map of all the running plot job objects
        std::vector<JobMan::individualConfig> getPlotJobConfigs();
        // checks for running plots on startup, creates plotjob objects if there are
        void _initRunningPlotsOnStart();
        // returns a vector of all the strings of paths leading to .pltjob files in temp dirs
        std::vector<std::string> findAllPlotJobStateFiles();

        // member config class object
        Config config = Config("/home/chia/Documents/plotalot_dev/test/config.txt"); // TODO generate absolute path

        // a vector that stores all running instances of plot jobs
        std::vector< PlotJob > runningPlotJobVector;
};
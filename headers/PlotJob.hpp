#pragma once

#include <string>
#include <array>
#include <unordered_map>
#include <vector>


// 1. class is constructed and given configMap and whether or not to restore
// 2. if not restore
//      a. build the command, save the log file name and command to the config
//      b. 

class PlotJob {
    public:
        typedef std::unordered_map<std::string, std::string> configMap;

        PlotJob(configMap config, bool restore = false);
        // begins plotting
        void begin();
        // suspends the plotting process
        void suspend();
        // resumes the suspended plot
        void resume();
        // kills a plot and clears its files
        void kill();
        // returns the config map of the plotJob
        configMap getConfigMap();

        void setPhase(struct phaseInfo info);



    private:

        // builds the command to run chia_plot given the arguments
        std::string buildCommand();

        long runCommand(std::string command);

        std::string getVal(const std::string& key);

        configMap jobConfig;
        bool jobRestore;                            //if jobRestore = true, do not run the start command
        std::string logFile;                        //path to the log file of the plot 
        struct phaseInfo {                          //plase and table its on (might not end up using this?)
            int currentPhase;                       
            int currentTable;
            int phase1Duration;
            int phase2Duration;
            int phase3Duration;
            int phase4Duration;
            int totalDuration;
            int movePlotDuration;
        };

    //plot arguments
        // int         jobThreads;                     //threads
        // int         jobBuckets;                     //buckets
        // int         jobBucketsp34;                  //buckets for phase 3 and 4
        // std::string jobTempDir;                     //temporary directory
        // std::string jobTempDirRAM;                  //temporary RAM disk
        // std::string jobDestination;                 //destination directory
        // bool        jobWait = NULL;                 //wait until copy is done to start next plot
        // std::string jobPoolPubKey;                  //pool public key (48 bytes)
        // std::string jobContactAddress;              //contract address (62 chars)
        // std::string jobFarmerPublicKey;             //farmer public key (48 bytes)
        // bool        jobAlternateTmp1Tmp2 = NULL;    //alternate tmpdir/tmpdir2 (default=false)
        // int         jobThreadMultiplier;            //thread multiplier for phase 2 (default=1)


        // plottingThreadMultiplier
        // plottingContractAddress
        // plottingPoolPubKey
        // plottingDestination
        // plottingBuckets34
        // plottingWait
        // plottingBuckets
        // plottingTempDirRAM
        // plottingTempDir
        // plottingTempDir
        // plottingThreads
};

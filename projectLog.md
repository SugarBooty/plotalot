7-28-21
I have made the code that makes multiple instnces of the plotjob class, figured out how to read from it, all that good stuff. Now I need to work on the plotjob class and making it run the chia command and all that.

For the plotjob I need to:
    - run the chia command, fork it, and obtain the PID for it
    - be able to suspend it using SIGPAUSE or something like that
    - be able to resume it using SIGRESUME or something like that

all the logic for restoring from state file is done, all the logic for generating state file is done

everything is coming along nicely

soon I will be able to test this on the chia server, which is exciting but scary.

I am losing motivation and drive to work on this project, I will soon need to rely on solely discipline for this.
My intention was that I would post it on the internet and people would use this to plot chia, but theres already so many alternatives mine will be lost in the ether. I will still use it, if it works alright, and the statistics functions will be cool. I just have so much to do. I only just barely have the base plotting functionality down and I still need to make bot programs for my full goal. I learned a lot about c++ and I guess I should be happy about that but I want to see this project work, I think, but I dont really know what I want.

I guess that in the very least, I can say that I made it if I actually make it work.

CLI stats page:

PlotID      Temp Drive      Dest Drive      Phase              Time
8Y65FFSU    /mnt/ssd2       /mnt/hdd8       [2:4]       7m30



7-27-21
Matt cleaned up the code for me, I was having compile issues and was getting no information on them. 
I have learned that g++ is much better for development, as clang++ doesnt give as detailed of errors and only compiles what runs. I was compiling looking for errors and when I tried g++ a lot of errors popped up. They've all been fixed

In the future, I will need to rewrite the config class so its not reeading from the file every time it gets data, but I will incorporate either a file watcher or a way to reload the config file through the CLI

Tommorrow I want to finish the code for making the state file for the job object, and after that who knows

I think I'm getting better at c++, but Rust is next. Make files are awful. No one should have to write explicit test code.

I was getting little information on the traceback from clang, when I switched to g++ I had a much better time and it revealed so many more errors.

7-26-21
So far I have added the getOptimalDestDrive functionality. I still need to add handling to wait to start a plot if no suitable drives are found

Temp files:

In the temp directory, there will be a .pltobj file for each plotjob object that can be read in the same format as the config to use the same parser.
The name will be the plotjob ID which will be either a random string, the epoch, time and date, something unique

In addition to this, the output of the plotting command will be piped into a file in either the temp directory or the root directory from which the program is run. This will be parsed for phase information on the current plot

In the case of a bootup with a dirty temp directory, I'm not certain how to deal with this. I could scan the PIDs to see if any plotters are running, if none are running it wipes the dirty temp directory and starts a new plot

7-25-21
I made the command builder for the chia command, now I need to work on finding the best option for the working drive and the destination drive. This will probably be done with a filesystem class 


7-24-21
My goal remains the same, make the config work
With the help of Matt I managed to get it to parse the config line of key=value1,value2,value3 into a 
pair of key, vector of value1, value2, value3. Now I need to finalize writing up the class functions and it will be correctly parsing the
config file and returning what it needs to

The config class can now return a umap of the keys and values from the config file


7-23-21
Current goal: make config work

worked on the config class, its more of a pain than I expected. Got it to be able to fun a function on each line of the config file



7-22-21
figured out how classes, header files, linking, types, all that works in cpp
I made a rough outline of the plotJob header file that contains a class whos objects will be the plots running
next I need to make the actual functions work and add to them

what I need to do next is:
    X figure out how to do a config file (make a config class to read from it)
        X I want to be able to change the config file and have plotalot read from it the nest itteration automatically
          This involves not storing any config options but reading from them whenever they are needed
    - figure out how to run the plotting command
    - figure out how to get the pid of the chia_plot command to stop and resume it
        X see if I can make a -a flag for it to stop and resume all plots
        X (I can using the .pltjob files)
    X make the function to build the plotting command
    - make the function that will extrapolate data from the log file of the plot
    - make a make file for the project, or use cmake or something to generate it automatically
        - screw that so far

nicities:
    X make the arrays in the plotJob class closer to what they actually need to be
        X (I just used strings)
    - figure out if I actually need a filestructure for the project or if I should keep all the files in one folder
    - 
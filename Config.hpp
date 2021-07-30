#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

class Config {
    public:
        typedef std::string configKeyStr;
        typedef std::string configValStr;
        typedef std::vector<std::string> configValueVec;
        typedef std::optional< std::pair<configKeyStr, configValueVec> > optionalConfigEntry;
        typedef std::pair<configKeyStr, configValueVec> configEntry;
        typedef std::unordered_map<configKeyStr, configValueVec> configMap;
        typedef std::unordered_map<configKeyStr, configValStr> configMapSingle;

        Config(const std::string& path) : configPath(path) {}

//      READ FUNCTIONS:

//      this function would be used if you have a lot of config files needed, so you can read throuht the map
        configMap getMappedConfig();
        configMapSingle getMappedConfig(std::string path);
        std::vector<std::string> getValues(const std::string& key) const;
        std::string getValue(const std::string& key) const;
        std::vector<std::string> getValuesFromMap(const configMap& map, const std::string& key) const;
        std::string getValueFromMap(const configMapSingle& map, const std::string& key) const;

//      WRITE FUNCTIONS:

        bool createFileFromMap(const configMap& map, const std::string& path);
        bool createFileFromMap(const configMapSingle& map, const std::string& path);

    private:
        std::string configPath;
        configMap parseConfigFile() const;
        configMapSingle parseConfigFile(std::string path) const;
        optionalConfigEntry parseLine(const std::string& line) const;
        std::vector<std::string> getValFromMap(const std::string& key, const configMap& map) const;
        std::string getValFromMap(const std::string& key, const configMapSingle& map) const;
        bool writeToFile(const std::string& content, const std::string& path);

};

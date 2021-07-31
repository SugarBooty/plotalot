#include "../headers/Config.hpp"

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <optional>
#include <filesystem>

// READ FUNCIONS

// returns an unordered map of all the config options, useful if you're using a lot of them
Config::configMap Config::getMappedConfig() {
    return parseConfigFile();
}

Config::configMapSingle Config::getMappedConfig(std::string path) {
    return parseConfigFile(path);
}

// returns a vector of a certain keys value(s)
std::vector<std::string> Config::getValues(const std::string& key) const {
    configMap configmap = parseConfigFile();
    return getValFromMap(key, configmap);
}

// returns a string for the value of a key
std::string Config::getValue(const std::string& key) const {
    configMap configmap = parseConfigFile();
    std::vector<std::string> valVec = getValFromMap(key, configmap);
    if (valVec.size() > 1)
        throw(std::invalid_argument("Config::getValue() expected a single value to be returned for key: " + key + " but got " + std::to_string(valVec.size())));
    return valVec.front();
}

std::vector<std::string> Config::getValuesFromMap(const configMap& map, const std::string& key) const {
    return getValFromMap(key, map);
}
        
std::string Config::getValueFromMap(const configMapSingle& map, const std::string& key) const {
    return getValFromMap(key, map);
}

// this is the command run for every line of the config file
Config::optionalConfigEntry Config::parseLine(const std::string& line) const {
    std::istringstream issLine(line);

    std::string key;
    std::getline(issLine, key, '=');
    if (line == key) return std::nullopt;

    std::vector<std::string> values;
    std::string value;
    while ( std::getline(issLine, value, ',') )
        values.push_back(value);
    Config::configEntry returnPair;
    returnPair.first = key;
    returnPair.second = values;

    return returnPair;
}

// this is what runs to read the config file line by line
Config::configMap Config::parseConfigFile() const {
    std::ifstream configFile (configPath);
    std::string line;
    configMap returnMap;
    if ( configFile.is_open() ) {
        while ( std::getline (configFile, line) ) {
            optionalConfigEntry out = parseLine(line);
            if (out) {
                const std::string& key = out->first;
                const std::vector<std::string>& valVec = out->second;
                returnMap[key] = valVec;
            }
        }
        return returnMap;
    }
    else
        throw(std::invalid_argument("Config file invalid!") );
}

Config::configMapSingle Config::parseConfigFile(std::string path) const {
    std::ifstream configFile (path);
    std::string line;
    configMapSingle returnMap;
    if ( configFile.is_open() ) {
        while ( std::getline (configFile, line) ) {
            optionalConfigEntry out = parseLine(line);
            if (out) {
                const std::string& key = out->first;
                const std::vector<std::string>& valVec = out->second;
                const std::string val = valVec[0];
                returnMap[key] = val;
            }
        }
        return returnMap;
    }
    else
        throw(std::invalid_argument("Config file invalid!") );
}

// this finds a key's value in the specified unordered map
std::vector<std::string> Config::getValFromMap(const std::string& key, const configMap& map) const {
    auto itr = map.find(key);
    if ( itr != map.end() )
        return itr->second;
    else
        throw(std::invalid_argument("No key called " + key + " found in config. Check the config file for typos."));
}

std::string Config::getValFromMap(const std::string& key, const configMapSingle& map) const {
    auto itr = map.find(key);
    if ( itr != map.end() )
        return itr->second;
    else
        throw(std::invalid_argument("No key called " + key + " found in config. Check the config file for typos."));
}


// WRITE FUNCTIONS:

bool Config::createFileFromMap(const configMap& map, const std::string& path) {
    std::ofstream plotJobConfigFile;
    plotJobConfigFile.open(path);
    if ( !plotJobConfigFile ){
        std::string valueString;
        for (auto [configKey, configValueVector] : map) {
            for ( std::string configValue : configValueVector )
                valueString += configValue + ",";
            plotJobConfigFile << configKey << "=" << valueString << std::endl;
        }
        plotJobConfigFile.close();
        return true;
    } else {
        std::cout << "Config file could not be created at " << path << std::endl;
        return false;
    }

}

bool Config::createFileFromMap(const configMapSingle& map, const std::string& path) {
    std::ofstream plotJobConfigFile;
    plotJobConfigFile.open(path);
    if ( !plotJobConfigFile ){
        for (auto [configKey, configValue] : map) {
            plotJobConfigFile << configKey << "=" << configValue << std::endl;
        }
        plotJobConfigFile.close();
        return true;
    } else {
        std::cout << "State file could not be created at " << path << " thus plot will be deleted in the event of plotalot-d restart" << std::endl;
        return false;
    }
}

// TODO make function that alters the config file
bool Config::writeToFile(const std::string& content, const std::string& path) {
    std::ofstream file;
    file.open(path);
    file << "Hello World" << std::endl;
    file.close();
    
    return true;
}

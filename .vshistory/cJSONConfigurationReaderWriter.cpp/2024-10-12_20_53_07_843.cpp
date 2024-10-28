#include "cJSONConfigurationReaderWriter.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

bool cJSONConfigurationReaderWriter::ReadConfig(sConfig& config)
{
    std::ifstream inputFile("config.json");
    if (!inputFile.is_open()) {
        std::cerr << "error opening file" << std::endl;
        return false;
    }

    // parse the json from the file;
    nlohmann::json jsonData;
    inputFile >> jsonData;

    configOut.Name = jsonData["Name"];

    if (!jsonData.contains("Player")) {
        return false;
    }
    if (!ParsePlayer(jsonData["Player"], configOut.Player)) {
        return false;
    }

    return true;
}

bool cJSONConfigurationReaderWriter::WriteConfig(const sConfig& config)
{
    return false;
}

bool cJSONConfigurationReaderWriter::ReadPreferences(sPreferences& preferences)
{
    return false;
}

bool cJSONConfigurationReaderWriter::WritePreferences(const sPreferences& preferences)
{
    return false;
}

bool cJSONConfigurationReaderWriter::ReadLanguage(sLanguage& language, const std::string& languageFile)
{
    return false;
}

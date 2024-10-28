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

    config.preferenceFileName = jsonData["preferenceFileName"];
    config.listOfLanguages["English"] = jsonData["English"];
    config.listOfLanguages["GenZ English"] = jsonData["Genz English"];

    std::cout << config.preferenceFileName << std::endl;
    std::cout << config.listOfLanguages["English"] << std::endl;
    std::cout << config.listOfLanguages["GenZ English"] << std::endl;
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

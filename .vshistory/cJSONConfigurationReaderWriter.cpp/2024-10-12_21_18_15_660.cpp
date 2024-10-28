#include "cJSONConfigurationReaderWriter.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

bool cJSONConfigurationReaderWriter::ReadConfig(sConfig& config)
{
    std::ifstream inputFile("config.json");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open config file." << std::endl;
        return false;
    }

    nlohmann::json jsonData;
    try {
        inputFile >> jsonData;
    }
    catch (nlohmann::json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        inputFile.close();
        return false;
    }

    inputFile.close();

    try {
        // Read the preferences file name
        config.preferenceFileName = jsonData.at("preferenceFileName").get<std::string>();

        // Populate language files from the listOfLanguages array
        for (const auto& item : jsonData.at("listOfLanguages").at("language")) {
            std::string langName = item.at("languageName").get<std::string>();
            std::string langFile = item.at("languageFile").get<std::string>();
            config.listOfLanguages[langName] = langFile; // Assuming languageFiles is a map
        }
    }
    catch (nlohmann::json::exception& e) {
        std::cerr << "Error accessing JSON data: " << e.what() << std::endl;
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

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
    nlohmann::json jsonData;

    // Populate jsonData with the structure we want
    jsonData["preferenceFileName"] = config.preferenceFileName;

    // Prepare the list of languages
    nlohmann::json languages = nlohmann::json::array();

    // Assuming config.languageFiles is a std::vector or a std::map
    for (const auto& language : config.listOfLanguages) {
        nlohmann::json languageEntry;

        // If language is a pair (std::map or std::unordered_map)
        languageEntry["languageName"] = language.first;   // Language name
        languageEntry["languageFile"] = language.second;   // Language file name

        languages.push_back(languageEntry);
    }

    // Set the languages into the jsonData
    jsonData["listOfLanguages"]["language"] = languages;

    // Write the jsonData to the file
    std::ofstream outputFile("config.json");
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open config file for writing." << std::endl;
        return false;
    }

    outputFile << jsonData.dump(4); // Pretty print with an indent of 4 spaces
    outputFile.close();

    return true;
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

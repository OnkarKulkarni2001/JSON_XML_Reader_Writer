#include "cJSONConfigurationReaderWriter.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

bool cJSONConfigurationReaderWriter::ReadConfig(sConfig& config)
{
    std::ifstream inputFile("config.json"); // Path to your JSON config file
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open config file." << std::endl;
        return false;
    }

    nlohmann::json jsonData;
    try {
        inputFile >> jsonData; // Read JSON data into jsonData
    }
    catch (nlohmann::json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        inputFile.close();
        return false;
    }

    inputFile.close(); // Close the file after reading

    // Populate the config data structure from JSON data
    //try {
        config.preferenceFileName = jsonData.at("preferenceFileName").get<std::string>();

        // Populate language files
        for (auto& item : jsonData.at("listOfLanguages").items()) {
            config.listOfLanguages[item.key()] = item.value().get<std::string>();
        }

        // You can add more options here as needed
    //}
    /*catch (nlohmann::json::exception& e) {
        std::cerr << "Error accessing JSON data: " << e.what() << std::endl;
        return false;
    }*/

    return true; // Successful read
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

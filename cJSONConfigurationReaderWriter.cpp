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
    std::cout << config.listOfLanguages["English"] << std::endl;
    std::cout << config.listOfLanguages["GenZ English"] << std::endl;
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
    std::ifstream inputFile("preference.json");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open preferences file." << std::endl;
        return false;
    }

    nlohmann::json jsonData;
    try {
        inputFile >> jsonData; // Read the JSON data from the file
    }
    catch (const std::exception& e) {
        std::cerr << "Error reading JSON data: " << e.what() << std::endl;
        return false;
    }

    // Extract data from the JSON object
    try {
        preferences.languagePreference = jsonData.at("languagePreference").get<std::string>();
        preferences.preferenceNumber = jsonData.at("preferenceNumber").get<int>();
        preferences.displayName = jsonData.at("displayName").get<std::string>();
        preferences.animalFriend = jsonData.at("animalFriend").get<std::string>();

        // You can add more preferences extraction here as needed
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Error accessing JSON data: " << e.what() << std::endl;
        return false;
    }
    return true;
}

bool cJSONConfigurationReaderWriter::WritePreferences(const sPreferences& preferences)
{
    nlohmann::json jsonData;

    // Populate the jsonData object with preference values
    jsonData["languagePreference"] = preferences.languagePreference;
    jsonData["preferenceNumber"] = preferences.preferenceNumber;
    jsonData["displayName"] = preferences.displayName;
    jsonData["animalFriend"] = preferences.animalFriend;

    // Write the JSON object to a file
    std::ofstream outputFile("preference.json");
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open preferences file for writing." << std::endl;
        return false;
    }

    try {
        outputFile << jsonData.dump(4); // Write JSON with 4 spaces of indentation
    }
    catch (const std::exception& e) {
        std::cerr << "Error writing JSON data: " << e.what() << std::endl;
        return false;
    }

    outputFile.close();
    return true;
}

bool cJSONConfigurationReaderWriter::ReadLanguage(sLanguage& language, const std::string& languageFile)
{
    std::ifstream inputFile(languageFile);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open language file." << std::endl;
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
        
        for (const auto& item : jsonData.at("languageTranslations").items()) {
            std::string key = item.key();
            std::string value = item.value();
            language.translations[key] = value;
        }
    }
    catch (nlohmann::json::exception& e) {
        std::cerr << "Error accessing JSON data: " << e.what() << std::endl;
        return false;
    }

    return true;
}

void cJSONConfigurationReaderWriter::PrintPreferences(sPreferences& preferences)
{
    std::cout << "Language: " << preferences.languagePreference << std::endl;
    std::cout << "Lucky Number: " << preferences.preferenceNumber << std::endl;
    std::cout << "Display Name: " << preferences.displayName << std::endl;
    std::cout << "Animal Friend: " << preferences.animalFriend << std::endl;
}

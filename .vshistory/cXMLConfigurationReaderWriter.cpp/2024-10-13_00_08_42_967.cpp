#include "cXMLConfigurationReaderWriter.h"
#include <iostream>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <pugixml/pugixml.hpp>
#include <pugixml/pugiconfig.hpp>

bool cXMLConfigurationReaderWriter::ReadConfig(sConfig& config)
{
    // Open and read the XML file using rapidxml::file for easier file management
    rapidxml::file<> xmlFile("config.xml"); // Loads and parses the XML file into memory

    // Create an XML document object
    rapidxml::xml_document<> doc;

    try {
        // Parse the XML content
        doc.parse<0>(xmlFile.data());
    }
    catch (const rapidxml::parse_error& e) {
        std::cerr << "Failed to parse XML: " << e.what() << std::endl;
        return false;
    }

    // Get the root element ("config")
    rapidxml::xml_node<>* root = doc.first_node("config");
    if (!root) {
        std::cerr << "Failed to find <config> element." << std::endl;
        return false;
    }

    // Read the <preferenceFileName>
    rapidxml::xml_node<>* preferenceFileNameNode = root->first_node("preferenceFileName");
    if (!preferenceFileNameNode) {
        std::cerr << "Failed to find <preferenceFileName> element." << std::endl;
        return false;
    }
    config.preferenceFileName = preferenceFileNameNode->value();

    // Find the <listOfLanguages> node
    rapidxml::xml_node<>* listOfLanguagesNode = root->first_node("listOfLanguages");
    if (!listOfLanguagesNode) {
        std::cerr << "Failed to find <listOfLanguages> element." << std::endl;
        return false;
    }

    // Iterate through each <language> node
    for (rapidxml::xml_node<>* languageNode = listOfLanguagesNode->first_node("language");
        languageNode != nullptr;
        languageNode = languageNode->next_sibling("language")) {

        // Read <languageName> and <languageFile> inside <language>
        rapidxml::xml_node<>* languageNameNode = languageNode->first_node("languageName");
        rapidxml::xml_node<>* languageFileNode = languageNode->first_node("languageFile");

        if (languageNameNode && languageFileNode) {
            std::string langName = languageNameNode->value();
            std::string langFile = languageFileNode->value();

            // Store in the map
            config.listOfLanguages[langName] = langFile;
        }
        else {
            std::cerr << "Failed to find <languageName> or <languageFile> in one of the <language> elements." << std::endl;
            return false;
        }
    }

    return true;
}

bool cXMLConfigurationReaderWriter::WriteConfig(const sConfig& config)
{
    // Create an XML document object
    pugi::xml_document doc;

    // Add XML declaration
    pugi::xml_node declaration = doc.prepend_child(pugi::node_declaration);
    declaration.append_attribute("version") = "1.0";
    declaration.append_attribute("encoding") = "utf-8";

    // Create root node <config>
    pugi::xml_node root = doc.append_child("config");

    // Add <preferenceFileName> node
    root.append_child("preferenceFileName").text().set(config.preferenceFileName.c_str());

    // Create <listOfLanguages> node
    pugi::xml_node listOfLanguagesNode = root.append_child("listOfLanguages");

    // Iterate through the languages in the config and add them as <language> nodes
    for (const auto& language : config.listOfLanguages) {
        // Create <language> node
        pugi::xml_node languageNode = listOfLanguagesNode.append_child("language");

        // Add <languageName> and <languageFile> nodes
        languageNode.append_child("languageName").text().set(language.first.c_str());
        languageNode.append_child("languageFile").text().set(language.second.c_str());
    }

    // Save the document to the output file
    if (!doc.save_file("config.xml")) {
        std::cerr << "Failed to save XML configuration to file." << std::endl;
        return false;
    }

    return true;
}

bool cXMLConfigurationReaderWriter::ReadPreferences(sPreferences& preferences)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("preference.xml");

    if (!result) {
        std::cerr << "Failed to open preferences file: " << result.description() << std::endl;
        return false;
    }

    // Locate the root element
    pugi::xml_node root = doc.child("preferences");
    if (!root) {
        std::cerr << "Error: 'preferences' root node not found." << std::endl;
        return false;
    }

    try {
        // Extract the languagePreference
        pugi::xml_node languageNode = root.child("languagePreference");
        if (languageNode) {
            preferences.languagePreference = languageNode.text().as_string();
        }
        else {
            std::cerr << "Error: 'languagePreference' node not found." << std::endl;
            return false;
        }

        // Extract the preferenceNumber
        pugi::xml_node numberNode = root.child("preferenceNumber");
        if (numberNode) {
            preferences.preferenceNumber = numberNode.text().as_int();
        }
        else {
            std::cerr << "Error: 'preferenceNumber' node not found." << std::endl;
            return false;
        }

        // Extract the animalFriend
        pugi::xml_node animalNode = root.child("animalFriend");
        if (animalNode) {
            preferences.animalFriend = animalNode.text().as_string();
        }
        else {
            std::cerr << "Error: 'animalFriend' node not found." << std::endl;
            return false;
        }

        // Extract the displayName
        pugi::xml_node nameNode = root.child("displayName");
        if (nameNode) {
            preferences.displayName = nameNode.text().as_string();
        }
        else {
            std::cerr << "Error: 'displayName' node not found." << std::endl;
            return false;
        }

        // You can add more preference extractions as needed here
    }
    catch (const std::exception& e) {
        std::cerr << "Error accessing XML data: " << e.what() << std::endl;
        return false;
    }
    std::cout << preferences.languagePreference << std::endl;
    std::cout << preferences.preferenceNumber << std::endl;
    std::cout << preferences.displayName << std::endl;
    std::cout << preferences.animalFriend << std::endl;
    return true;
}

bool cXMLConfigurationReaderWriter::WritePreferences(const sPreferences& preferences)
{
    pugi::xml_document doc;

    // Create the root node
    pugi::xml_node root = doc.append_child("preferences");

    // Add the languagePreference node
    pugi::xml_node languageNode = root.append_child("languagePreference");
    languageNode.append_child(pugi::node_pcdata).set_value(preferences.languagePreference.c_str());

    // Add the preferenceNumber node
    pugi::xml_node numberNode = root.append_child("preferenceNumber");
    numberNode.append_child(pugi::node_pcdata).set_value(std::to_string(preferences.preferenceNumber).c_str());

    // Add the animalFriend node
    pugi::xml_node animalNode = root.append_child("animalFriend");
    animalNode.append_child(pugi::node_pcdata).set_value(preferences.animalFriend.c_str());
    
    // Add the displayName node
    pugi::xml_node displayNode = root.append_child("displayName");
    displayNode.append_child(pugi::node_pcdata).set_value(preferences.displayName.c_str());

    // Write the XML document to a file
    std::ofstream outputFile("preference.xml");
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open preferences file for writing." << std::endl;
        return false;
    }

    // Save the XML document to the output file
    doc.save(outputFile, "  ");  // Indent with 2 spaces
    outputFile.close();

    return true;
}

bool cXMLConfigurationReaderWriter::ReadLanguage(sLanguage& language, const std::string& languageFile)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(languageFile.c_str());

    if (!result) {
        std::cerr << "Failed to open language file: " << result.description() << std::endl;
        return false;
    }

    // Access the <languageTranslations> node
    pugi::xml_node translationsNode = doc.child("languageTranslations");

    // Check if the node exists
    if (!translationsNode) {
        std::cerr << "<languageTranslations> node not found in the XML file." << std::endl;
        return false;
    }

    // Iterate through the children of <languageTranslations>
    for (pugi::xml_node translationNode = translationsNode.first_child(); translationNode; translationNode = translationNode.next_sibling()) {
        std::string key = translationNode.name(); // The name of the node is the key
        std::string value = translationNode.text().as_string(); // The text of the node is the value
        language.translations[key] = value; // Store the translation in the map
    }

    return true;
}
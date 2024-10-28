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

        // Extract the preferenceString
        pugi::xml_node stringNode = root.child("preferenceString");
        if (stringNode) {
            preferences.preferenceString = stringNode.text().as_string();
        }
        else {
            std::cerr << "Error: 'preferenceString' node not found." << std::endl;
            return false;
        }

        // You can add more preference extractions as needed here
    }
    catch (const std::exception& e) {
        std::cerr << "Error accessing XML data: " << e.what() << std::endl;
        return false;
    }

    return true;
}

bool cXMLConfigurationReaderWriter::WritePreferences(const sPreferences& preferences)
{
    return false;
}

bool cXMLConfigurationReaderWriter::ReadLanguage(sLanguage& language, const std::string& languageFile)
{
    return false;
}

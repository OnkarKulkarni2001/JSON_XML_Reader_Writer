#include "cXMLConfigurationReaderWriter.h"
#include <iostream>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <fstream>

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
    rapidxml::xml_document<> doc;

    // Add XML declaration
    rapidxml::xml_node<>* declaration = doc.allocate_node(rapidxml::node_declaration);
    declaration->append_attribute(doc.allocate_attribute("version", "1.0"));
    declaration->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
    doc.append_node(declaration);

    // Create root node <config>
    rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "config");
    doc.append_node(root);

    // Add <preferenceFileName> node
    rapidxml::xml_node<>* preferenceFileNameNode = doc.allocate_node(
        rapidxml::node_element, "preferenceFileName", config.preferenceFileName.c_str());
    root->append_node(preferenceFileNameNode);

    // Create <listOfLanguages> node
    rapidxml::xml_node<>* listOfLanguagesNode = doc.allocate_node(rapidxml::node_element, "listOfLanguages");
    root->append_node(listOfLanguagesNode);

    // Iterate through the languages in the config and add them as <language> nodes
    for (const auto& language : config.listOfLanguages) {
        // Create <language> node
        rapidxml::xml_node<>* languageNode = doc.allocate_node(rapidxml::node_element, "language");

        // Allocate and add <languageName> and <languageFile> nodes
        rapidxml::xml_node<>* languageNameNode = doc.allocate_node(
            rapidxml::node_element, "languageName", doc.allocate_string(language.first.c_str()));
        rapidxml::xml_node<>* languageFileNode = doc.allocate_node(
            rapidxml::node_element, "languageFile", doc.allocate_string(language.second.c_str()));

        languageNode->append_node(languageNameNode);
        languageNode->append_node(languageFileNode);

        // Append <language> node to <listOfLanguages>
        listOfLanguagesNode->append_node(languageNode);
    }

    // Convert the XML document to a string for saving
    std::ofstream outputFile("config.xml");
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open config file for writing." << std::endl;
        return false;
    }

    // Write the XML document to the file
    outputFile << doc;
    outputFile.close();

    return true;
}

bool cXMLConfigurationReaderWriter::ReadPreferences(sPreferences& preferences)
{
    return false;
}

bool cXMLConfigurationReaderWriter::WritePreferences(const sPreferences& preferences)
{
    return false;
}

bool cXMLConfigurationReaderWriter::ReadLanguage(sLanguage& language, const std::string& languageFile)
{
    return false;
}

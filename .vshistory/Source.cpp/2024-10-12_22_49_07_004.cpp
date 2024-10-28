#include <iostream>
#include "iConfigurationReaderWriter.h"
#include "cJSONConfigurationReaderWriter.h"
#include "cXMLConfigurationReaderWriter.h"
#include "structs.h"

int main() {
	iConfigurationReaderWriter* readerWriter(0);
	//readerWriter = new cJSONConfigurationReaderWriter();
	readerWriter = new cXMLConfigurationReaderWriter();
	
	sConfig config;
	readerWriter->ReadConfig(config);

	std::cout << config.preferenceFileName << std::endl;
	std::cout << config.listOfLanguages["English"] << std::endl;
	std::cout << config.listOfLanguages["GenZ English"] << std::endl;

	readerWriter->WriteConfig(config);
	std::cout << config.preferenceFileName << std::endl;
	std::cout << config.listOfLanguages["English"] << std::endl;
	std::cout << config.listOfLanguages["GenZ English"] << std::endl;

	sPreferences preferences;
	readerWriter->ReadPreferences(preferences);
	std::cout << preferences.languagePreference << std::endl;
	std::cout << preferences.preferenceNumber << std::endl;
	std::cout << preferences.preferenceString << std::endl;

	preferences.languagePreference = "English";
	preferences.preferenceNumber = 1;
	preferences.preferenceString = "low";
	readerWriter->WritePreferences(preferences);

	//sLanguage language;
	//std::string languageFile = "genzEnglish.xml";
	//readerWriter->ReadLanguage(language, languageFile);
	//std::cout << language.translations["welcome"] << std::endl;
	//std::cout << language.translations["exit"] << std::endl;

	return 0;
}
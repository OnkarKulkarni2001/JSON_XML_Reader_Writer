#include <iostream>
#include "iConfigurationReaderWriter.h"
#include "cJSONConfigurationReaderWriter.h"
#include "cXMLConfigurationReaderWriter.h"
#include "structs.h"
#include "cTranslator.h"

int main() {
	//iConfigurationReaderWriter* readerWriter(0);
	////readerWriter = new cJSONConfigurationReaderWriter();
	//readerWriter = new cXMLConfigurationReaderWriter();
	//
	//sConfig config;
	//readerWriter->ReadConfig(config);
	//std::cout << config.preferenceFileName << std::endl;
	//std::cout << config.listOfLanguages["English"] << std::endl;
	//std::cout << config.listOfLanguages["GenZ English"] << std::endl;

	//std::cout << config.preferenceFileName << std::endl;
	//std::cout << config.listOfLanguages["GenZ English"] << std::endl;
	//std::cout << config.listOfLanguages["English"] << std::endl;
	//readerWriter->WriteConfig(config);

	//sPreferences preferences;
	//readerWriter->ReadPreferences(preferences);
	//std::cout << preferences.languagePreference << std::endl;
	//std::cout << preferences.preferenceNumber << std::endl;
	//std::cout << preferences.animalFriend << std::endl;

	//preferences.languagePreference = "English";
	//preferences.preferenceNumber = 1;
	//preferences.animalFriend = "low";
	//readerWriter->WritePreferences(preferences);

	//sLanguage language;
	//std::string languageFile = "genzEnglish.xml";
	//readerWriter->ReadLanguage(language, languageFile);
	//std::cout << language.translations["welcome"] << std::endl;
	//std::cout << language.translations["exit"] << std::endl;
	cTranslator translator;
	translator.StartTranslator();
	return 0;
}
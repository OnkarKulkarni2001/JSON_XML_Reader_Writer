#include "cTranslator.h"
#include "structs.h"
#include "iConfigurationReaderWriter.h"
#include "cJSONConfigurationReaderWriter.h"
#include "cXMLConfigurationReaderWriter.h"
#include <iostream>

void cTranslator::StartTranslator()
{
	iConfigurationReaderWriter* readerWriter(0);
	readerWriter = new cJSONConfigurationReaderWriter();
	readerWriter = new cXMLConfigurationReaderWriter();

	sLanguage language;
	std::string languageFile = "genzEnglish.xml";
	readerWriter->ReadLanguage(language, languageFile);
	std::cout << language.translations["welcome"] << std::endl;
	std::cout << language.translations["exit"] << std::endl;
	std::cout << language.translations["currentPreferences"] << std::endl;

	sPreferences preferences;
	readerWriter->ReadPreferences(preferences);
	std::cout << preferences.languagePreference << std::endl;
	std::cout << preferences.preferenceNumber << std::endl;
	std::cout << preferences.displayName << std::endl;
	std::cout << preferences.animalFriend << std::endl;

	std::cout << language.translations["setPreferences"] << std::endl;
	int number = 1;
	std::cin >> number;
	switch (number) {
	case 1:
		std::cout << language.translations["setLanguagePreference"] << std::endl;
		std::cin >> preferences.languagePreference;
		readerWriter->WritePreferences(preferences);
		std::cout << language.translations["updatedLanguagePreference"] << std::endl;
		break;
	case 2:
		std::cout << language.translations["setDisplayNamePreference"] << std::endl;
		std::cin >> preferences.displayName;
		readerWriter->WritePreferences(preferences);
		std::cout << language.translations["updatedDisplayNamePreference"] << std::endl;
		break;
	case 3:
		std::cout << language.translations["setNumberPreference"] << std::endl;
		std::cin >> preferences.preferenceNumber;
		readerWriter->WritePreferences(preferences);
		std::cout << language.translations["updatedNumberPreference"] << std::endl;
		break;
	case 4:
		std::cout << language.translations["setAnimalFriendPreference"] << std::endl;
		std::cin >> preferences.animalFriend;
		readerWriter->WritePreferences(preferences);
		std::cout << language.translations["updatedAnimalFriendPreference"] << std::endl;
		break;
	default:
		std::cout << language.translations["setLanguagePreference"] << std::endl;
		std::cin >> preferences.languagePreference;
		readerWriter->WritePreferences(preferences);
		std::cout << language.translations["updatedLanguagePreference"] << std::endl;
		break;
	}

	std::cout << language.translations["currentPreferences"] << std::endl;

}

void cTranslator::QuitTranslator()
{

}

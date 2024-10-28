#pragma once
#include <string>
#include <map>

struct sConfig {
	std::string preferenceFileName;
	std::map<std::string, std::string> listOfLanguages;		// List of language names and corresponding files
};

struct sPreferences {
	string languagePreference;									// 1) Language preference
	int preferenceNumber;									// From list of 1, 2, 3, 4... where 1 for language
															// 2 for display name
															// 3 for number
															// 4 for pet name
	std::string preferenceString;							// maybe a value from list of high, low, medium 
};

struct sLanguage {
	std::map<std::string, std::string> translations;		// key value pairs, values are translations for keys from json/xml files
};
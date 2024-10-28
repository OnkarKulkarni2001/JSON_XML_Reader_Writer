#pragma once
#include "structs.h"
#include "iConfigurationReaderWriter.h"
class cLibrary
{
private:
	sLanguage language;

public:
	bool LoadLanguage(const std::string& languageFile, iConfigurationReaderWriter& readerWriter);
	std::string GetString(const std::string& key);
};
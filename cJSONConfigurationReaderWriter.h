#pragma once
#include "iConfigurationReaderWriter.h"

class cJSONConfigurationReaderWriter : public iConfigurationReaderWriter
{
public:
	bool ReadConfig(sConfig& config) override;
	bool WriteConfig(const sConfig& config) override;

	bool ReadPreferences(sPreferences& preferences) override;
	bool WritePreferences(const sPreferences& preferences) override;

	bool ReadLanguage(sLanguage& language, const std::string& languageFile) override;
	void PrintPreferences(sPreferences& preferences) override;
};
#pragma once
#include "structs.h"
class iConfigurationReaderWriter
{
public:
	virtual bool ReadConfig(sConfig& config) = 0;
	virtual bool WriteConfig(const sConfig& config) = 0;

	virtual bool ReadPreferences(sPreferences& preferences) = 0;
	virtual bool WritePreferences(const sPreferences& preferences) = 0;

	virtual bool ReadLanguage(sLanguage& language, const std::string& languageFile) = 0;
	virtual void PrintPreferences(sPreferences& preferences) override;

	virtual ~iConfigurationReaderWriter() {}
};
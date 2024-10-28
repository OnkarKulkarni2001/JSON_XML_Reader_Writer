#include "cLibrary.h"

bool cLibrary::LoadLanguage(const std::string& languageFile, iConfigurationReaderWriter& readerWriter)
{
    return readerWriter.ReadLanguage(language, languageFile);
}

std::string cLibrary::GetString(const std::string& key)
{
    if (language.translations.find(key) != language.translations.end()) {
        return language.translations[key];
    }
    return "Translation not found";
}

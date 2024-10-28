#include "cTranslator.h"
#include "structs.h"

void cTranslator::StartTranslator()
{
	sLanguage language;
	std::string languageFile = "genzEnglish.xml";
	readerWriter->ReadLanguage(language, languageFile);
	std::cout << language.translations["welcome"] << std::endl;
	std::cout << language.translations["exit"] << std::endl;
}

void cTranslator::QuitTranslator()
{

}

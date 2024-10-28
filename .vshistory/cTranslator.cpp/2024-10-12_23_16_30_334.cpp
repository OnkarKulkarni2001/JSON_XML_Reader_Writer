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
}

void cTranslator::QuitTranslator()
{

}

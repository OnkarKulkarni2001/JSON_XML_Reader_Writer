#include <iostream>
#include "iConfigurationReaderWriter.h"
#include "cJSONConfigurationReaderWriter.h"
#include "structs.h"

int main() {
	iConfigurationReaderWriter* readerWriter(0);
	readerWriter = new cJSONConfigurationReaderWriter();
	
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
	return 0;
}
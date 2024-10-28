#include <iostream>
#include "iConfigurationReaderWriter.h"
#include "cJSONConfigurationReaderWriter.h"
#include "structs.h"

int main() {
	iConfigurationReaderWriter* readerWriter(0);
	readerWriter = new cJSONConfigurationReaderWriter();
	
	sConfig config;
	readerWriter->ReadConfig(config);
	return 0;
}
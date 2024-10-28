#include <iostream>
#include "iConfigurationReaderWriter.h"
#include "cJSONConfigurationReaderWriter.h"
#include "cXMLConfigurationReaderWriter.h"
#include "structs.h"
#include "cTranslator.h"

int main() {
	cTranslator translator;
	translator.StartTranslator();
	return 0;
}
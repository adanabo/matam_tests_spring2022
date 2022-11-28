//
// Created by Adana on 27/11/2022.
//

#ifndef ASCIIARTTOOL_C_ASCIIARTTOOL_H
#define ASCIIARTTOOL_C_ASCIIARTTOOL_H
#include "../RLEList.h"



RLEList asciiArtRead(FILE* in_stream);

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);


#endif //ASCIIARTTOOL_C_ASCIIARTTOOL_H

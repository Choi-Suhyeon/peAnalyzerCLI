//
// Created by 최수현 on 2022/05/02.
//

#ifndef PEANALCLI_IMAGEFILEHEADER_H
#define PEANALCLI_IMAGEFILEHEADER_H

#include "abstractPEStruct.h"

class imageFileHeader: protected AbstractPEStruct {
    const char * const * const kNameArr = new const char *[getNumOfElem()] {
        "Machine",         "NumberOfSections",     "TimeDataStamp",   "PointerToSymbolTable",
        "NumberOfSymbols", "SizeOfOptionalHeader", "Characteristics"
    };

    const char * const * const kDescArr = new const char *[getNumOfElem()] {
        "The number that identifies the type of target machine",
        "The size of the section table",
        "The number which indicates when the file was created",
        "",
        "",
        "",
        "The flags that indicate the attributes of the file"
    };
};


#endif //PEANALCLI_IMAGEFILEHEADER_H

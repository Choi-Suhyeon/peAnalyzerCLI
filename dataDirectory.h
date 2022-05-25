//
// Created by 최수현 on 2022/05/24.
//

#ifndef PEANALCLI_DATADIRECTORY_H
#define PEANALCLI_DATADIRECTORY_H

#include "abstractPEStruct.h"

class DataDirectory final: protected AbstractPEStruct {
    const size_t    kNumOfVal = getNumOfElem() / 2 - 1;
    ConstCStringArr kValArr   = new ConstCString [kNumOfVal] {
        "IMAGE_DIRECTORY_ENTRY_EXPORT",    "IMAGE_DIRECTORY_ENTRY_IMPORT",       "IMAGE_DIRECTORY_ENTRY_RESOURCE",
        "IMAGE_DIRECTORY_ENTRY_EXCEPTION", "IMAGE_DIRECTORY_ENTRY_SECURITY",     "IMAGE_DIRECTORY_ENTRY_BASERELOC",
        "IMAGE_DIRECTORY_ENTRY_DEBUG",     "IMAGE_DIRECTORY_ENTRY_COPYRIGHT",    "IMAGE_DIRECTORY_ENTRY_GLOBALPTR",
        "IMAGE_DIRECTORY_ENTRY_TLS",       "IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG",  "IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT",
        "IMAGE_DIRECTORY_ENTRY_IAT",       "IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT", "IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR"
    };

public:
    explicit DataDirectory(TargetFile *, size_t);

    void print() final;
};


#endif //PEANALCLI_DATADIRECTORY_H

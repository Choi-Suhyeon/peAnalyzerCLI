#ifndef PEANALCLI_IMAGEIMPORTDESCRIPTOR_H
#define PEANALCLI_IMAGEIMPORTDESCRIPTOR_H

#include "../header/abstractPEStruct.h"
#include "../file_byte/targetFile.h"

class ImageImportDescriptor final: protected AbstractPEStruct {
public:
    ImageImportDescriptor(TargetFile *, size_t);
};


#endif //PEANALCLI_IMAGEIMPORTDESCRIPTOR_H

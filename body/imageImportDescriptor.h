#ifndef PEANALCLI_IMAGEIMPORTDESCRIPTOR_H
#define PEANALCLI_IMAGEIMPORTDESCRIPTOR_H

#include "../header/abstractPEStruct.h"
#include "../file_byte/targetFile.h"

class ImageImportDescriptor final: protected AbstractPEStruct {
    const size_t    kNumOfElem_ = getNumOfElem();
    ConstCStringArr kNameArr_   = new ConstCString [kNumOfElem_] {
            "OriginalFirstThunk", "TimeDateStamp", "ForwarderChain",
            "Name",               "FirstThunk"
    };
    const char * kImportedObjNm = nullptr;

public:
    ImageImportDescriptor(TargetFile *, size_t, std::list<SizeTPair> *);
    ~ImageImportDescriptor();

    void print() const final;

    [[nodiscard]] size_t getNextIIDAdr();
};

#endif //PEANALCLI_IMAGEIMPORTDESCRIPTOR_H

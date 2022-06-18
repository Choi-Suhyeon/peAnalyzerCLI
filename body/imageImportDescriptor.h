#ifndef PEANALCLI_IMAGEIMPORTDESCRIPTOR_H
#define PEANALCLI_IMAGEIMPORTDESCRIPTOR_H

#include "../header/abstractPEStruct.h"
#include "../file_byte/targetFile.h"
#include <list>

class ImageImportDescriptor final: protected AbstractPEStruct {
    const size_t    kNumOfElem_ = getNumOfElem();
    ConstCStringArr kNameArr_   = new ConstCString [kNumOfElem_] {
            "OriginalFirstThunk", "TimeDateStamp", "ForwarderChain",
            "Name",               "FirstThunk"
    };
    std::list<std::pair<const short, const char *>> imp_by_nm_lst;
    const char * kImportedLibNm = nullptr;

    ConstCString getName(size_t);
    void printIAT() const;

public:
    static const size_t StructSize;

    ImageImportDescriptor(TargetFile *, size_t, std::list<std::pair<size_t, size_t>> *);
    ~ImageImportDescriptor() final;

    void print() const final;

    [[nodiscard]] size_t getNextIIDAdr();
};


#endif //PEANALCLI_IMAGEIMPORTDESCRIPTOR_H

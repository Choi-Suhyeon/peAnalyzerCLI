#ifndef PEANALCLI_IMAGEIMPORTDESCRIPTOR_H
#define PEANALCLI_IMAGEIMPORTDESCRIPTOR_H

#include "../header/abstractPEStruct.h"
#include "../file_byte/targetFile.h"
#include <list>

using HintName = std::pair<const short, const char *>;

class ImageImportDescriptor final: protected AbstractPEStruct {
    const size_t    kNumOfElem_    = getNumOfElem(),
                    kPtrSzOfIIN_   = getIs32bit() ? kSzOfDWORD_ : kSzOfQWORD_;
    ConstCStringArr kNameArr_      = new ConstCString [kNumOfElem_] {
            "OriginalFirstThunk", "TimeDateStamp", "ForwarderChain",
            "Name",               "FirstThunk"
    };
    const char   * kImportedLibNm_ = nullptr;

    size_t              first_thunk_   = 0;
    std::list<HintName> imp_by_nm_lst_;

    ConstCString getName(size_t);
    void printIAT() const;

public:
    static const size_t StructSize_;

    ImageImportDescriptor(TargetFile *, size_t, SizeTPairList *);
    ~ImageImportDescriptor() final;

    void print() const final;

    [[nodiscard]] size_t getNextIIDAdr();
};


#endif //PEANALCLI_IMAGEIMPORTDESCRIPTOR_H

#ifndef PEANALCLI_IMAGESECTIONHEADER_H
#define PEANALCLI_IMAGESECTIONHEADER_H

#include "abstractPEStruct.h"
#include <algorithm>

class ImageSectionHeader final: protected AbstractPEStruct {
    const size_t    kNumOfElem   = getNumOfElem(),
                    kNumOfChars  = 16,
                    kSzOfName    = 8;
    ConstCStringArr kNameArr     = new ConstCString [kNumOfElem] {
        "VirtualSize",         "VirtualAddress",       "SizeOfRawData",
        "PointerToRawData",    "PointerToRelocations", "PointerToLinenumbers",
        "NumberOfRelocations", "NumberOfLinenumbers",  "Characteristics"
    };
    ConstSizeTArr kSizeArr       = new ConstSizeT [kNumOfElem] {
        kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_,
        kSzOfDWORD_, kSzOfWORD_,  kSzOfWORD_,  kSzOfDWORD_
    };
    ConstSizeTArr kCharsNumArr   = new ConstSizeT [kNumOfChars] {
        0x00000020, 0x00000040, 0x00000080,
        0x00000200, 0x00000800,
        0x00001000, 0x00004000, 0x00008000,
        0x01000000, 0x02000000, 0x04000000, 0x08000000,
        0x10000000, 0x20000000, 0x40000000, 0x80000000
    };
    ConstCStringArr kCharsValArr = new ConstCString [kNumOfChars] {
        "IMAGE_SCN_CNT_CODE",        "IMAGE_SCN_CNT_INITIALIZED_DATA", "IMAGE_SCN_CNT_UNINITIALIZED_DATA",
        "IMAGE_SCN_LNK_INFO",        "IMAGE_SCN_LNK_REMOVE",
        "IMAGE_SCN_LNK_COMDAT",      "IMAGE_SCN_NO_DEFER_SPEC_EXC",    "IMAGE_SCN_GPREL",
        "IMAGE_SCN_LNK_NRELOC_OVFL", "IMAGE_SCN_MEM_DISCARDABLE",      "IMAGE_SCN_MEM_NOT_CACHED", "IMAGE_SCN_MEM_NOT_PAGED",
        "IMAGE_SCN_MEM_SHARED",      "IMAGE_SCN_MEM_EXECUTE",          "IMAGE_SCN_MEM_READ",       "IMAGE_SCN_MEM_WRITE"
    };

    char * name          = new char [kSzOfName + 1];
    size_t data_of_chars = 0;

    void printCharacteristics() const;

public:
    explicit ImageSectionHeader(TargetFile *, size_t);
    ~ImageSectionHeader() final;

    void print() const final;

    [[nodiscard]] size_t getNextAdrOfSectionHeader() const;
};


#endif //PEANALCLI_IMAGESECTIONHEADER_H

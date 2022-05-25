#ifndef PEANALCLI_IMAGEOPTIONALHEADER32_H
#define PEANALCLI_IMAGEOPTIONALHEADER32_H

#include "optionalHeaderInterface.h"
#include "abstractPEStruct.h"
#include "targetFile.h"

class ImageOptionalHeader32 final: protected AbstractPEStruct, protected OptionalHeaderInterface {
    const size_t    kNumOfElem = getNumOfElem();
    ConstCStringArr kNameArr   = new ConstCString [kNumOfElem] {
        "Magic",                        "MajorLinkerVersion",          "MinorLinkerVersion",
        "SizeOfCode",                   "SizeOfInitializedData",       "SizeOfUninitializedData",
        "AddressOfEntryPoint",          "BaseOfCode",                  "BaseOfData",
        "ImageBase",                    "SectionAlignment",            "FileAlignment",
        "MajorOperatingSystemVersion",  "MinorOperatingSystemVersion", "MajorImageVersion",
        "MinorImageVersion",            "MajorSubsystemVersion",       "MinorSubsystemVersion",
        "Win32VersionValue",            "SizeOfImage",                 "SizeOfHeaders",
        "CheckSum",                     "Subsystem",                   "DllCharacteristics",
        "SizeOfStackReserve",           "SizeOfStackCommit",           "SizeOfHeapReserve",
        "SizeOfHeapCommit",             "LoaderFlags",                 "NumberOfRvaAndSizes"
    };
    ConstSizeTArr   kSizeArr   = new ConstSizeT [kNumOfElem] {
        kSzOfWORD_,  kSzOfBYTE_,  kSzOfBYTE_,  kSzOfDWORD_, kSzOfDWORD_,
        kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_,
        kSzOfDWORD_, kSzOfDWORD_, kSzOfWORD_,  kSzOfWORD_,  kSzOfWORD_,
        kSzOfWORD_,  kSzOfWORD_,  kSzOfWORD_,  kSzOfDWORD_, kSzOfDWORD_,
        kSzOfDWORD_, kSzOfDWORD_, kSzOfWORD_,  kSzOfWORD_,  kSzOfDWORD_,
        kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_
    };

public:
    explicit ImageOptionalHeader32(TargetFile *, size_t);
    ~ImageOptionalHeader32() final;

    void print() final;

    [[nodiscard]] size_t getInitialAdrOfDataDir() const;
};


#endif //PEANALCLI_IMAGEOPTIONALHEADER32_H

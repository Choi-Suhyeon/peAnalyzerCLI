//
// Created by 최수현 on 2022/05/24.
//

#ifndef PEANALCLI_IMAGEOPTIONALHEADER64_H
#define PEANALCLI_IMAGEOPTIONALHEADER64_H

#include "optionalHeaderInterface.h"
#include "abstractPEStruct.h"
#include "targetFile.h"

class ImageOptionalHeader64 final: protected AbstractPEStruct, protected OptionalHeaderInterface {
    const size_t    kNumOfElem = getNumOfElem();
    ConstCStringArr kNameArr   = new ConstCString [kNumOfElem] {
        "Magic",                       "MajorLinkerVersion",    "MinorLinkerVersion",
        "SizeOfCode",                  "SizeOfInitializedData", "SizeOfUninitializedData",
        "AddressOfEntryPoint",         "BaseOfCode",            "ImageBase",
        "SectionAlignment",            "FileAlignment",         "MajorOperatingSystemVersion",
        "MinorOperatingSystemVersion", "MajorImageVersion",     "MinorImageVersion",
        "MajorSubsystemVersion",       "MinorSubsystemVersion", "Win32VersionValue",
        "SizeOfImage",                 "SizeOfHeaders",         "CheckSum",
        "Subsystem",                   "DllCharacteristics",    "SizeOfStackReserve",
        "SizeOfStackCommit",           "SizeOfHeapReserve",     "SizeOfHeapCommit",
        "LoaderFlags",                 "NumberOfRvaAndSizes"
    };
    ConstSizeTArr   kSizeArr   = new ConstSizeT [kNumOfElem] {
        kSzOfWORD_,  kSzOfBYTE_,  kSzOfBYTE_,  kSzOfDWORD_, kSzOfDWORD_,
        kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_, kSzOfQWORD_, kSzOfDWORD_,
        kSzOfDWORD_, kSzOfWORD_,  kSzOfWORD_,  kSzOfWORD_,  kSzOfWORD_,
        kSzOfWORD_,  kSzOfWORD_,  kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_,
        kSzOfDWORD_, kSzOfWORD_,  kSzOfWORD_,  kSzOfQWORD_, kSzOfQWORD_,
        kSzOfQWORD_, kSzOfQWORD_, kSzOfDWORD_, kSzOfDWORD_
    };

public:
    explicit ImageOptionalHeader64(TargetFile &, size_t);
    ~ImageOptionalHeader64() final;

    void print() final;
};


#endif //PEANALCLI_IMAGEOPTIONALHEADER64_H

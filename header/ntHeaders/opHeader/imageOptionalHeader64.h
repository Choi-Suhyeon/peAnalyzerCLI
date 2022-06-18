//
// Created by 최수현 on 2022/05/24.
//

#ifndef PEANALCLI_IMAGEOPTIONALHEADER64_H
#define PEANALCLI_IMAGEOPTIONALHEADER64_H

#include "optionalHeaderInterface.h"
#include "../../abstractPEStruct.h"
#include "../../../file_byte/targetFile.h"

class ImageOptionalHeader64 final: protected AbstractPEStruct, protected OptionalHeaderInterface {
    const size_t    kNumOfElem_ = getNumOfElem();
    ConstCStringArr kNameArr_   = new ConstCString [kNumOfElem_] {
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
    ConstSizeTArr   kSizeArr_   = new ConstSizeT [kNumOfElem_] {
        kSzOfWORD_,  kSzOfBYTE_,  kSzOfBYTE_,  kSzOfDWORD_, kSzOfDWORD_,
        kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_, kSzOfQWORD_, kSzOfDWORD_,
        kSzOfDWORD_, kSzOfWORD_,  kSzOfWORD_,  kSzOfWORD_,  kSzOfWORD_,
        kSzOfWORD_,  kSzOfWORD_,  kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_,
        kSzOfDWORD_, kSzOfWORD_,  kSzOfWORD_,  kSzOfQWORD_, kSzOfQWORD_,
        kSzOfQWORD_, kSzOfQWORD_, kSzOfDWORD_, kSzOfDWORD_
    };

public:
    explicit ImageOptionalHeader64(TargetFile *, size_t);

    void print() const final;

    [[nodiscard]] size_t getInitialAdrOfDataDir() const;
};


#endif //PEANALCLI_IMAGEOPTIONALHEADER64_H

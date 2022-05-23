#ifndef PEANALCLI_IMAGEOPTIONALHEADER32_H
#define PEANALCLI_IMAGEOPTIONALHEADER32_H

#include "abstractPEStruct.h"
#include "targetFile.h"

class ImageOptionalHeader32 final: protected AbstractPEStruct {
    const size_t    kNumSubSys = 17,
                    kNumOfElem = getNumOfElem();
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
    ConstCStringArr kSubSysArr = new ConstCString [kNumSubSys] {
        "IMAGE_SUBSYSTEM_UNKNOWN",                  "IMAGE_SUBSYSTEM_NATIVE",
        "IMAGE_SUBSYSTEM_WINDOWS_GUI",              "IMAGE_SUBSYSTEM_WINDOWS_CUI",
        "",                                         "IMAGE_SUBSYSTEM_OS2_CUI",
        "",                                         "IMAGE_SUBSYSTEM_POSIX_CUI",
        "IMAGE_SUBSYSTEM_NATIVE_WINDOWS",           "IMAGE_SUBSYSTEM_WINDOWS_CE_GUI",
        "IMAGE_SUBSYSTEM_EFI_APPLICATION",          "IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER",
        "IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER",       "IMAGE_SUBSYSTEM_EFI_ROM",
        "IMAGE_SUBSYSTEM_XBOX",                     "",
        "IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION"
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
    explicit ImageOptionalHeader32(TargetFile &, size_t);
    ~ImageOptionalHeader32() final;

    void print() final;
};


#endif //PEANALCLI_IMAGEOPTIONALHEADER32_H

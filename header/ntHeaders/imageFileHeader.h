#ifndef PEANALCLI_IMAGEFILEHEADER_H
#define PEANALCLI_IMAGEFILEHEADER_H

#include "../abstractPEStruct.h"
#include "../../file_byte/targetFile.h"
#include <algorithm>
#include <ctime>

class ImageFileHeader final: protected AbstractPEStruct {
    const size_t    kNumOfChar_     = 16,
                    kNumOfMachine_  = 29,
                    kNumOfElem_     = getNumOfElem();
    ConstCStringArr kNameArr_       = new ConstCString [kNumOfElem_] {
        "Machine",         "NumberOfSections",     "TimeDataStamp",   "PointerToSymbolTable",
        "NumberOfSymbols", "SizeOfOptionalHeader", "Characteristics"
    };
    ConstSizeTArr   kSizeArr_       = new ConstSizeT [kNumOfElem_] {
        kSzOfWORD_, kSzOfWORD_, kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_, kSzOfWORD_, kSzOfWORD_
    };
    ConstCStringArr kDescOfCharArr_ = new ConstCString [kNumOfChar_] {
            "IMAGE_FILE_RELOCS_STRIPPED",         "IMAGE_FILE_EXECUTABLE_IMAGE",
            "IMAGE_FILE_LINE_NUMS_STRIPPED",      "IMAGE_FILE_LOCAL_SYMS_STRIPPED",
            "IMAGE_FILE_AGGRESIVE_WS_TRIM",       "IMAGE_FILE_LARGE_ADDRESS_AWARE",
            "IMAGE_FILE_BYTES_REVERSED_LO",       "",
            "IMAGE_FILE_32BIT_MACHINE",           "IMAGE_FILE_DEBUG_STRIPPED",
            "IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP", "IMAGE_FILE_NET_RUN_FROM_SWAP",
            "IMAGE_FILE_SYSTEM",                  "IMAGE_FILE_DLL",
            "IMAGE_FILE_UP_SYSTEM_ONLY",          "IMAGE_FILE_BYTES_REVERSED_HI"
    };
    ConstSizeTArr kMachineNumArr_   = new ConstSizeT [kNumOfMachine_] {
            0x0000, 0x014C, 0x0162, 0x0166, 0x0168, 0x0169, 0x0184,
            0x01A2, 0x01A3, 0x01A4, 0x01A6, 0x01A8, 0x01C0, 0x01C2,
            0x01C4, 0x01D3, 0x01F0, 0x01F1, 0x0200, 0x0266, 0x0284,
            0x0366, 0x0466, 0x0520, 0x0CEF, 0x0EBC, 0x8664, 0x9041, 0xC0EE
    };
    ConstCStringArr kMachineValArr_ = new ConstCString [kNumOfMachine_] {
            "IMAGE_FILE_MACHINE_UNKNOWN", "IMAGE_FILE_MACHINE_I386",      "IMAGE_FILE_MACHINE_R3000",
            "IMAGE_FILE_MACHINE_R4000",   "IMAGE_FILE_MACHINE_R10000",    "IMAGE_FILE_MACHINE_WCEMIPSV2",
            "IMAGE_FILE_MACHINE_ALPHA",   "IMAGE_FILE_MACHINE_SH3",       "IMAGE_FILE_MACHINE_SH3DSP",
            "IMAGE_FILE_MACHINE_SH3E",    "IMAGE_FILE_MACHINE_SH4",       "IMAGE_FILE_MACHINE_SH5",
            "IMAGE_FILE_MACHINE_ARM",     "IMAGE_FILE_MACHINE_THUMB",     "IMAGE_FILE_MACHINE_ARMNT",
            "IMAGE_FILE_MACHINE_AM33",    "IMAGE_FILE_MACHINE_POWERPC",   "IMAGE_FILE_MACHINE_POWERPCFP",
            "IMAGE_FILE_MACHINE_IA64",    "IMAGE_FILE_MACHINE_MIPS16",    "IMAGE_FILE_MACHINE_ALPHA64",
            "IMAGE_FILE_MACHINE_MIPSFPU", "IMAGE_FILE_MACHINE_MIPSFPU16", "IMAGE_FILE_MACHINE_TRICORE",
            "IMAGE_FILE_MACHINE_CEF",     "IMAGE_FILE_MACHINE_EBC",       "IMAGE_FILE_MACHINE_AMD64",
            "IMAGE_FILE_MACHINE_M32R",    "IMAGE_FILE_MACHINE_CEE"
    };

    unsigned short data_of_chars_;

    char * getMachineVal(size_t);
    void printCharacteristics() const;

public:
    explicit ImageFileHeader(TargetFile *, size_t);
    ~ImageFileHeader() final;

    void print() const final;

    [[nodiscard]] size_t getInitialAdrOfOpHd() const;
    [[nodiscard]] size_t getNumberOfSections() const;
};

#endif //PEANALCLI_IMAGEFILEHEADER_H

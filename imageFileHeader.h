#ifndef PEANALCLI_IMAGEFILEHEADER_H
#define PEANALCLI_IMAGEFILEHEADER_H

#include "abstractPEStruct.h"
#include "targetFile.h"
#include <cstring>
#include <ctime>

class ImageFileHeader final: protected AbstractPEStruct {
    const unsigned                     kNumOfChar     = 4;
    const char * const * const         kNameArr       = new const char *[getNumOfElem()] {
        "Machine",         "NumberOfSections",     "TimeDataStamp",   "PointerToSymbolTable",
        "NumberOfSymbols", "SizeOfOptionalHeader", "Characteristics"
    };
    const char * const * const         kDescArr       = new const char *[getNumOfElem()] {
        "The number that identifies the type of target machine",
        "The size of the section table",
        "The number which indicates when the file was created",
        "The file offset of the COFF symbol table",
        "The number of entries in the symbol table",
        "The size of the optional header, which is required for executable files",
        "The flags that indicate the attributes of the file"
    };
    const unsigned * const             kSizeArr       = new const unsigned[getNumOfElem()] {
        kSzOfWORD_, kSzOfWORD_, kSzOfDWORD_, kSzOfDWORD_, kSzOfDWORD_, kSzOfWORD_, kSzOfWORD_
    };
    const char * const * const * const kDescOfCharArr = new const char * const *[kNumOfChar] {
        new const char *[4] {
            "IMAGE_FILE_RELOCS_STRIPPED",    "IMAGE_FILE_EXECUTABLE_IMAGE",
            "IMAGE_FILE_LINE_NUMS_STRIPPED", "IMAGE_FILE_LOCAL_SYMS_STRIPPED"
        },
        new const char *[3] {
            "IMAGE_FILE_AGGRESIVE_WS_TRIM", "IMAGE_FILE_LARGE_ADDRESS_AWARE",
            "IMAGE_FILE_BYTES_REVERSED_LO"
        },
        new const char *[4] {
            "IMAGE_FILE_32BIT_MACHINE",           "IMAGE_FILE_DEBUG_STRIPPED",
            "IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP", "IMAGE_FILE_NET_RUN_FROM_SWAP"
        },
        new const char *[4] {
            "IMAGE_FILE_SYSTEM",         "IMAGE_FILE_DLL",
            "IMAGE_FILE_UP_SYSTEM_ONLY", "IMAGE_FILE_BYTES_REVERSED_HI"
        }
    };

    int * charIndices = new int[kNumOfChar];

public:
    explicit ImageFileHeader(TargetFile &, unsigned);
    ~ImageFileHeader() final;

    void print() final;

    [[nodiscard]] unsigned getInitialAdrOfOpHd();
};

#endif //PEANALCLI_IMAGEFILEHEADER_H

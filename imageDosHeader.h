#ifndef PEANALCLI_IMAGEDOSHEADER_H
#define PEANALCLI_IMAGEDOSHEADER_H

#import "abstractPEStruct.h"

class ImageDosHeader: protected AbstractPEStruct {
    static const unsigned kNumOfElem_ = 31;
    static const unsigned kSize_      = 0x40;
    const char ** const   kNameArr_   = new const char *[kNumOfElem_] {
            "e_magic",    "e_cblp",     "e_cp",     "e_crlc",  "e_cparhdr",
            "e_minalloc", "e_maxalloc", "e_ss",     "e_sp",    "e_csum",
            "e_ip",       "e_cs",       "e_lfarlc", "e_ovno",  "e_res",
            "e_res",      "e_res",      "e_res",    "e_oemid", "e_oeminfo",
            "e_res2",     "e_res2",     "e_res2",   "e_res2",  "e_res2",
            "e_res2",     "e_res2",     "e_res2",   "e_res2",  "e_res2",
            "e_lfanew"
    };
    const char ** const   kDescArr_   = new const char *[kNumOfElem_] {
            "MZ Header signature",              "Bytes on last page of file",
            "Pages in file",                    "Relocations",
            "Size of header in paragraphs",     "Minimum extra paragraphs needed",
            "Maximum extra paragraphs needed",  "Initial (relative) SS value",
            "Initial SP value",                 "Checksum",
            "Initial IP value",                 "Initial (relative) CS value",
            "File address of relocation table", "Overlay number",
            "Reserved words",                   "Reserved words",
            "Reserved words",                   "Reserved words",
            "OEM identifier (for e_oeminfo)",   "OEM information; e_oemid specific",
            "Reserved words",                   "Reserved words",
            "Reserved words",                   "Reserved words",
            "Reserved words",                   "Reserved words",
            "Reserved words",                   "Reserved words",
            "Reserved words",                   "Reserved words",
            "Offset to extended header"
    };

public:
    explicit ImageDosHeader(TargetFile &, unsigned);
    ~ImageDosHeader();

    void print() final;
};

#endif //PEANALCLI_IMAGEDOSHEADER_H

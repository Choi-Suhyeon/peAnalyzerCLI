#ifndef PEANALCLI_IMAGEDOSHEADER_H
#define PEANALCLI_IMAGEDOSHEADER_H

#include "abstractPEStruct.h"
#include "imageDosHeader.h"

class ImageDosHeader final: protected AbstractPEStruct {
    ConstCStringArr kNameArr_ = new ConstCString [getNumOfElem()] {
            "e_magic",    "e_cblp",     "e_cp",     "e_crlc",  "e_cparhdr",
            "e_minalloc", "e_maxalloc", "e_ss",     "e_sp",    "e_csum",
            "e_ip",       "e_cs",       "e_lfarlc", "e_ovno",  "e_res",
            "e_res",      "e_res",      "e_res",    "e_oemid", "e_oeminfo",
            "e_res2",     "e_res2",     "e_res2",   "e_res2",  "e_res2",
            "e_res2",     "e_res2",     "e_res2",   "e_res2",  "e_res2",
            "e_lfanew"
    };

public:
    explicit ImageDosHeader(TargetFile *, size_t);
    ~ImageDosHeader();

    void print() final;

    [[nodiscard]] size_t getInitialAdrOfNTHd();
};

#endif //PEANALCLI_IMAGEDOSHEADER_H

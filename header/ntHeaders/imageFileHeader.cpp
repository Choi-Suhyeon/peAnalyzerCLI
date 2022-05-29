#include "imageFileHeader.h"

void delNewLine(char * str) {
    while (*str++);
    if (str[-2] == '\n') str[-2] = '\0';
}

char * getTimeStamp(const size_t kData) {
    char * result = asctime(gmtime((time_t *) &kData));
    delNewLine(result);
    return result;
}

char * ImageFileHeader::getMachineVal(const size_t kData) {
    const size_t * kEndPos  = kMachineNumArr_ + kNumOfMachine_;
    const size_t * kElemPos = std::find(kMachineNumArr_, kEndPos, kData);

    return (char *)(kElemPos != kEndPos
            ? kMachineValArr_[kElemPos - kMachineNumArr_]
            : "");
}

void ImageFileHeader::printCharacteristics() const {
    for (size_t i = 0, filter = 1; i < kNumOfChar_; i++, filter <<= 1) {
        if (data_of_chars_ & filter && i ^ 7) {
            puts(kDescOfCharArr_[i]);
        }
    }
}

ImageFileHeader::ImageFileHeader(TargetFile * const kFile, const size_t kInitialAdr)
: AbstractPEStruct(kFile, kInitialAdr, 7, 0x14) {
    for (size_t i = 0, adr = 0; i < kNumOfElem_; adr += kSizeArr_[i++]) {
        const size_t kData  = getSubBytes(sub_bin_, adr, kSizeArr_[i]);
        const char * kValue =
                i == 0 ? getMachineVal(kData) :
                i == 2 ? getTimeStamp(kData)  :
                (char *)"";

        if (i == 6) data_of_chars_ = kData;

        elem_info_[i].name = kNameArr_[i];
        elem_info_[i].size = kSizeArr_[i];
        elem_info_[i].adr  = adr;
        elem_info_[i].val  = kValue;
    }
}

ImageFileHeader::~ImageFileHeader() {
    delete [] kNameArr_;
    delete [] kSizeArr_;
    delete [] kDescOfCharArr_;
}

void ImageFileHeader::print() const {
    puts("[IMAGE FILE HEADER]");
    AbstractPEStruct::print();
    printCharacteristics();
    puts("");
}

size_t ImageFileHeader::getInitialAdrOfOpHd() const {
    return getInitialAdr() + getSize();
}

size_t ImageFileHeader::getNumberOfSections() const {
    return getSubBytes(sub_bin_, elem_info_[1].adr, elem_info_[1].size);
}

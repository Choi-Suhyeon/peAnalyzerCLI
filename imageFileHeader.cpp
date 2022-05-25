#include "imageFileHeader.h"

ssize_t findIndex(const size_t * start, const size_t length, const size_t looking_for) {
    for (ssize_t i = 0; i < length; i++) {
        if (start[i] == looking_for) return i;
    }

    return -1;
}

void delNewLine(char * str) {
    while (*str++);
    if (str[-2] == '\n') str[-2] = '\0';
}

void ImageFileHeader::printCharacteristics() {
    unsigned short filter = 1;

    for (size_t i = 0; i < kNumOfChar; i++, filter <<= 1) {
        if (data_of_chars & filter && i ^ 7) {
            printf("%s\n", kDescOfCharArr[i]);
        }
    }
}

ImageFileHeader::ImageFileHeader(TargetFile * file, const size_t initial_adr)
: AbstractPEStruct(file, initial_adr, 7, 0x14) {
    using std::byte;

    for (size_t i = 0, current_adr = 0; i < kNumOfElem; current_adr += kSizeArr[i++]) {
        const size_t kData = TargetFile::getSubBytes(sub_bin_, current_adr, kSizeArr[i]);

        if (i == 6) data_of_chars = kData;

        char *value;
        switch(i) {
            case 2:
                value = asctime(gmtime((time_t *) &kData));
                delNewLine(value);
                break;
            case 0: {
                const ssize_t kIdx = findIndex(kMachineNumArr, kNumOfMachine, kData);
                if (kIdx != -1) {
                    value = (char *)kMachineValArr[kIdx];
                    break;
                }
            }
            default: value = (char *)"";
        }

        elem_info_[i].name = kNameArr[i];
        elem_info_[i].size = kSizeArr[i];
        elem_info_[i].adr  = current_adr;
        elem_info_[i].val  = value;
    }
}

ImageFileHeader::~ImageFileHeader() {
    delete [] kNameArr;
    delete [] kSizeArr;
    delete [] kDescOfCharArr;
}

void ImageFileHeader::print() {
    printf("[IMAGE FILE HEADER]\n");

    AbstractPEStruct::print();
    printCharacteristics();

    printf("\n");
}

size_t ImageFileHeader::getInitialAdrOfOpHd() {
    return getInitialAdr() + getSize();
}

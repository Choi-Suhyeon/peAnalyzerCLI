#include "imageOptionalHeader32.h"


ImageOptionalHeader32::ImageOptionalHeader32(TargetFile & file, size_t initial_adr)
: AbstractPEStruct(file, initial_adr, 30, 0x60) {
    using std::exception;

    for (size_t i = 0, current_adr = 0; i < kNumOfElem; current_adr += kSizeArr[i++]) {
        const size_t kSize = kSizeArr[i];
        const size_t kData = TargetFile::getSubBytes(sub_bin_, current_adr, kSize);

        char * value;
        switch (i) {
            case 0:
                if (kData ^ 0x10B) throw exception();
                value = (char *)"PE32";
                break;
            case 22:
                if (kData < kNumSubSys) {
                    value = (char *)kSubSysArr[kData];
                    break;
                }
            default: value = (char *)"";
        }

        elem_info_[i].name = kNameArr[i];
        elem_info_[i].size = kSize;
        elem_info_[i].adr  = current_adr;
        elem_info_[i].val  = value;
    }
}

ImageOptionalHeader32::~ImageOptionalHeader32() {
    delete [] kNameArr;
    delete [] kSubSysArr;
    delete [] kSizeArr;
}

void ImageOptionalHeader32::print() {
    printf("[IMAGE OPTIONAL HEADER 32]\n");
    AbstractPEStruct::print();
    printf("\n");
}

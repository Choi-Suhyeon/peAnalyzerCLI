#include "imageOptionalHeader64.h"

ImageOptionalHeader64::ImageOptionalHeader64(TargetFile & file, size_t initial_adr)
: AbstractPEStruct(file, initial_adr, 29, 0x70) {
    using std::exception;

    for (size_t i = 0, current_adr = 0; i < kNumOfElem; current_adr += kSizeArr[i++]) {
        const size_t kSize  = kSizeArr[i],
                     kData  = TargetFile::getSubBytes(sub_bin_, current_adr, kSize);
        const char * kValue =
                i == 0  ? getValOfMagic(kData)  :
                i == 21 ? getValOfSubSys(kData) :
                (char *)"";

        elem_info_[i].name = kNameArr[i];
        elem_info_[i].size = kSize;
        elem_info_[i].adr  = current_adr;
        elem_info_[i].val  = kValue;
    }
}

ImageOptionalHeader64::~ImageOptionalHeader64() {
    delete [] kNameArr;
    delete [] kSizeArr;
}

void ImageOptionalHeader64::print() {
    printf("[IMAGE OPTIONAL HEADER 64]\n");
    AbstractPEStruct::print();
    printf("\n");
}

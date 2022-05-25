#include "imageOptionalHeader32.h"


ImageOptionalHeader32::ImageOptionalHeader32(TargetFile * file, size_t initial_adr)
: AbstractPEStruct(file, initial_adr, 30, 0x60) {
    using std::exception;

    for (size_t i = 0, current_adr = 0; i < kNumOfElem; current_adr += kSizeArr[i++]) {
        const size_t kSize  = kSizeArr[i],
                     kData  = getSubBytes(sub_bin_, current_adr, kSize);
        const char * kValue =
                i == 0  ? getValOfMagic(kData)  :
                i == 22 ? getValOfSubSys(kData) :
                (char *)"";

        elem_info_[i].name = kNameArr[i];
        elem_info_[i].size = kSize;
        elem_info_[i].adr  = current_adr;
        elem_info_[i].val  = kValue;
    }
}

ImageOptionalHeader32::~ImageOptionalHeader32() {
    delete [] kNameArr;
    delete [] kSizeArr;
}

void ImageOptionalHeader32::print() {
    printf("[IMAGE OPTIONAL HEADER 32]\n");
    AbstractPEStruct::print();
    printf("\n");
}

size_t ImageOptionalHeader32::getInitialAdrOfDataDir() const {
    return getInitialAdr() + getSize();
}

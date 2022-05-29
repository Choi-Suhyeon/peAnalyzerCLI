#include "imageOptionalHeader32.h"


ImageOptionalHeader32::ImageOptionalHeader32(TargetFile * const kFile, const size_t kInitialAdr)
: AbstractPEStruct(kFile, kInitialAdr, 30, 0x60) {
    for (size_t i = 0, current_adr = 0; i < kNumOfElem_; current_adr += kSizeArr_[i++]) {
        const size_t kSize  = kSizeArr_[i],
                     kData  = getSubBytes(sub_bin_, current_adr, kSize);
        const char * kValue =
                i == 0  ? getValOfMagic(kData)  :
                i == 22 ? getValOfSubSys(kData) :
                (char *)"";

        elem_info_[i].name = kNameArr_[i];
        elem_info_[i].size = kSize;
        elem_info_[i].adr  = current_adr;
        elem_info_[i].val  = kValue;
    }
}

ImageOptionalHeader32::~ImageOptionalHeader32() {
    delete [] kNameArr_;
    delete [] kSizeArr_;
}

void ImageOptionalHeader32::print() const {
    puts("[IMAGE OPTIONAL HEADER 32]");
    AbstractPEStruct::print();
    puts("");
}

size_t ImageOptionalHeader32::getInitialAdrOfDataDir() const {
    return getInitialAdr() + getSize();
}

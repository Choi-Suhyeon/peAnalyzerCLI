#include "imageOptionalHeader64.h"

ImageOptionalHeader64::ImageOptionalHeader64(TargetFile * const kFile, const size_t kInitialAdr)
: AbstractPEStruct(kFile, kInitialAdr, 29, 0x70) {
    for (size_t i = 0, adr = 0; i < kNumOfElem_; adr += kSizeArr_[i++]) {
        const size_t kSize  = kSizeArr_[i],
                     kData  = getSubBytes(sub_bin_, adr, kSize);
        const char * kValue =
                i == 0  ? getValOfMagic(kData)  :
                i == 21 ? getValOfSubSys(kData) :
                (char *)"";

        elem_info_[i].name = kNameArr_[i];
        elem_info_[i].size = kSize;
        elem_info_[i].adr  = adr;
        elem_info_[i].val  = kValue;
    }

    delete [] kNameArr_;
    delete [] kSizeArr_;
}

void ImageOptionalHeader64::print() const {
    puts("[IMAGE OPTIONAL HEADER 64]");
    AbstractPEStruct::print();
    puts("");
}

size_t ImageOptionalHeader64::getInitialAdrOfDataDir() const {
    return getInitialAdr() + getSize();
}

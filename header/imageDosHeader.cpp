#include "imageDosHeader.h"

ImageDosHeader::ImageDosHeader(TargetFile * const kFile, const size_t kInitialAdr)
: AbstractPEStruct(kFile, kInitialAdr, 31, 0x40) {
    using std::byte;
    using std::fill_n;
    using std::memcpy;

    const size_t kNumOfElem = getNumOfElem(),
                 kLastIdx   = kNumOfElem - 1,
                 kPESig     = 0x5A4D;

    size_t sizeArr[kNumOfElem];
    fill_n(sizeArr, kLastIdx, kSzOfWORD_);
    sizeArr[kLastIdx] = kSzOfDWORD_;

    const size_t kFirstValue = getSubBytes(sub_bin_, 0, *sizeArr);

    for (size_t i = 0, adr = 0; i < kNumOfElem; adr += sizeArr[i++]) {
        elem_info_[i].name = kNameArr_[i];
        elem_info_[i].size = sizeArr[i];
        elem_info_[i].adr  = adr;
        elem_info_[i].val  = !i && kFirstValue == kPESig ? "PE file" : "";
    }
}

ImageDosHeader::~ImageDosHeader() {
    delete [] kNameArr_;
}

void ImageDosHeader::print() const {
    puts("[IMAGE DOS HEADER]");
    AbstractPEStruct::print();
    puts("");
}

size_t ImageDosHeader::getInitialAdrOfNTHd() {
    const size_t kLastIdx      = getNumOfElem() - 1,
                 kAdrLastElem  = elem_info_[kLastIdx].adr,
                 kSizeLastElem = elem_info_[kLastIdx].size;

    return getFile()->getFileContents(kAdrLastElem, kSizeLastElem);
}

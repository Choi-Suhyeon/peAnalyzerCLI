#include "imageDosHeader.h"

ImageDosHeader::ImageDosHeader(TargetFile & file, const unsigned initial_adr)
: AbstractPEStruct(file, initial_adr, 31, 0x40) {
    using std::byte;
    using std::fill_n;
    using std::memcpy;

    const unsigned kSize      = getSize();
    const unsigned kNumOfElem = getNumOfElem();
    const unsigned kPESig     = 0x5A4D;
    const unsigned kLastIdx   = getNumOfElem() - 1;

    sub_bin_ = new byte[kSize];
    getFile().getFileContents(sub_bin_, getInitialAdr(), kSize);

    unsigned sizeArr[kNumOfElem];
    fill_n(sizeArr, kLastIdx, kSzOfWORD_);
    sizeArr[kLastIdx] = kSzOfDWORD_;

    const unsigned kFirstValue = TargetFile::getSubBytes(sub_bin_, 0, *sizeArr);

    auto current_adr = new unsigned(0);
    for (unsigned i = kNumOfElem; i; i--) {
        const unsigned kIdx = kNumOfElem - i;

        elem_info_[kIdx].name = kNameArr_[kIdx];
        elem_info_[kIdx].desc = kDescArr_[kIdx];
        elem_info_[kIdx].size = sizeArr[kIdx];
        elem_info_[kIdx].adr  = *current_adr;
        elem_info_[kIdx].val  = !kIdx && kFirstValue == kPESig ? "PE file" : "";

        *current_adr += sizeArr[kIdx];
    }
    delete current_adr;
}

ImageDosHeader::~ImageDosHeader() {
    delete [] kNameArr_;
    delete [] kDescArr_;
}

void ImageDosHeader::print() {
    AbstractPEStruct::print();
    printf("\n");
}

unsigned ImageDosHeader::getInitialAdrOfNTHd() {
    const unsigned kLastIdx = getNumOfElem() - 1;
    const unsigned adr      = elem_info_[kLastIdx].adr;

    return getFile().getFileContents(adr, elem_info_[kLastIdx].size);
}

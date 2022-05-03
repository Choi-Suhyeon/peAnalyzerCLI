#include "imageDosHeader.h"

ImageDosHeader::ImageDosHeader(TargetFile & file, const unsigned initial_adr)
: AbstractPEStruct(file, initial_adr, 31, 0x40) {
    using std::byte;
    using std::fill_n;
    using std::memcpy;

    const bool     kIs32bit   = getIs32bit();
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

    auto * current_adr = new unsigned(0);
    for (unsigned i = kNumOfElem; i; i--) {
        const unsigned kIdx = kNumOfElem - i;

        elem_info_[kIdx].name = kNameArr_[kIdx];
        elem_info_[kIdx].desc = kDescArr_[kIdx];
        elem_info_[kIdx].size = sizeArr[kIdx];


        elem_info_[kIdx].val = !kIdx && kFirstValue == kPESig ? "PE file" : "";

        byte adr_bytes[kIs32bit ? kSzOfAdr32_ : kSzOfAdr64_];
        changeUnsignedToBytes(*current_adr, adr_bytes, sizeof adr_bytes);
        byte * adr_i = kIs32bit
                ? elem_info_[kIdx].adr.bit32
                : elem_info_[kIdx].adr.bit64;
        memcpy(adr_i, adr_bytes, sizeof adr_bytes);

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
}

unsigned ImageDosHeader::getInitialAdrOfNTHd() {
    const unsigned kLastIdx = getNumOfElem() - 1;
    const unsigned adr      = getIs32bit()
            ? changeBytesToUnsigned(elem_info_[kLastIdx].adr.bit32, kSzOfAdr32_)
            : changeBytesToUnsigned(elem_info_[kLastIdx].adr.bit64, kSzOfAdr64_);

    return getFile().getFileContents(adr, elem_info_[kLastIdx].size);
}

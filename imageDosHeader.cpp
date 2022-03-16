#include "imageDosHeader.h"

ImageDosHeader::ImageDosHeader(TargetFile & file, const unsigned initial_adr):
        AbstractPEStruct(file, initial_adr, kNumOfElem_, kSize_) {
    using std::byte;
    using std::fill_n;
    using std::memcpy;

    const unsigned kPESig   = 0x5A4D;
    const unsigned kLastIdx = kNumOfElem_ - 1;

    unsigned sizeArr[kNumOfElem_];
    fill_n(sizeArr, kLastIdx, getSzOfWORD());
    sizeArr[kLastIdx] = getSzOfDWORD();

    for (unsigned i = 0, current_adr = 0; i < kNumOfElem_; current_adr += sizeArr[i++]) {
        elem_info_[i].name = kNameArr_[i];
        elem_info_[i].desc = kDescArr_[i];
        elem_info_[i].size = sizeArr[i];

        const unsigned kValue = getFile().getFileContents(current_adr, *sizeArr);
        if (!i && kValue == kPESig) elem_info_->val   = "PE file";
        else                        elem_info_[i].val = "";

        byte adr_bytes[getIs32bit() ? getSzOfAdr32() : getSzOfAdr64()];
        changeUnsignedToBytes(current_adr, adr_bytes, sizeof adr_bytes);
        byte * adr_i = getIs32bit() ? elem_info_[i].adr.bit32 : elem_info_[i].adr.bit64;
        memcpy(adr_i, adr_bytes, sizeof adr_bytes);
    }
}

ImageDosHeader::~ImageDosHeader() {
    delete [] kNameArr_;
    delete [] kDescArr_;
}

void ImageDosHeader::print() {
    AbstractPEStruct::print();
}

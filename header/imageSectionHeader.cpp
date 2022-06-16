#include "imageSectionHeader.h"

void ImageSectionHeader::printCharacteristics() const {
    for (size_t i = 0, filter = 1; i < 8 * kSzOfDWORD_; i++, filter <<= 1) {
        size_t interim;

        if ((interim = data_of_chars_ & filter)) {
            const size_t * kEndPos  = kCharsNumArr_ + kNumOfChars_,
                         * kElemPos = std::find(kCharsNumArr_, kEndPos, interim);

            if (kElemPos != kEndPos) puts(kCharsValArr_[kElemPos - kCharsNumArr_]);
        }
    }
}

ImageSectionHeader::ImageSectionHeader(TargetFile * file, size_t initial_adr)
: AbstractPEStruct(file, initial_adr, 9, 0x28) {
    const size_t kLastIdx   = kNumOfElem_ - 1;

    auto temp_name = new std::byte [kSzOfName_];
    getSubBytes(temp_name, sub_bin_, 0, kSzOfName_);

    for (size_t i = 0; i < kSzOfName_; i++) name_[i] = char(temp_name[i]);
    name_[kSzOfName_] = '\0';

    delete [] temp_name;

    for (size_t i = 0, adr = kSzOfName_; i < kNumOfElem_; adr += kSizeArr_[i++]) {
        elem_info_[i].name = kNameArr_[i];
        elem_info_[i].size = kSizeArr_[i];
        elem_info_[i].adr  = adr;
        elem_info_[i].val  = "";
    }

    data_of_chars_ = getSubBytes(sub_bin_, elem_info_[kLastIdx].adr, elem_info_[kLastIdx].size);
}

ImageSectionHeader::~ImageSectionHeader() {
    delete [] kNameArr_;
    delete [] kSizeArr_;
    delete [] kCharsNumArr_;
    delete [] kCharsValArr_;
    delete [] name_;
}

void ImageSectionHeader::print() const {
    printf("[SECTION HEADER - %s]\n", name_);
    AbstractPEStruct::print();
    printCharacteristics();
    puts("");
}

size_t ImageSectionHeader::getNextAdrOfSectionHeader() const {
    return getInitialAdr() + getSize();
}

std::pair<size_t, size_t> ImageSectionHeader::getVaPtr2raw() const {
    size_t va      = getSubBytes(sub_bin_, elem_info_[1].adr, elem_info_[1].size),
           ptr2raw = getSubBytes(sub_bin_, elem_info_[3].adr, elem_info_[3].size);
    return std::make_pair(va, ptr2raw);
}

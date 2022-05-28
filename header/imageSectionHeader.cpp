#include "imageSectionHeader.h"

void ImageSectionHeader::printCharacteristics() const {
    for (size_t i = 0, filter = 1; i < 8 * kSzOfDWORD_; i++, filter <<= 1) {
        size_t interim;

        if ((interim = data_of_chars & filter)) {
            const size_t * kEndPos  = kCharsNumArr + kNumOfChars,
                         * kElemPos = std::find(kCharsNumArr, kEndPos, interim);

            if (kElemPos != kEndPos) puts(kCharsValArr[kElemPos - kCharsNumArr]);
        }
    }
}

ImageSectionHeader::ImageSectionHeader(TargetFile * file, size_t initial_adr)
: AbstractPEStruct(file, initial_adr, 9, 0x28) {
    const size_t kLastIdx   = kNumOfElem - 1;

    auto temp_name = new std::byte [kSzOfName];
    getSubBytes(temp_name, sub_bin_, 0, kSzOfName);

    for (size_t i = 0; i < kSzOfName; i++) name[i] = char(temp_name[i]);
    name[kSzOfName] = '\0';

    delete [] temp_name;

    for (size_t i = 0, adr = kSzOfName; i < kNumOfElem; adr += kSizeArr[i++]) {
        elem_info_[i].name = kNameArr[i];
        elem_info_[i].size = kSizeArr[i];
        elem_info_[i].adr  = adr;
        elem_info_[i].val  = "";
    }

    data_of_chars = getSubBytes(sub_bin_, elem_info_[kLastIdx].adr, elem_info_[kLastIdx].size);
}

ImageSectionHeader::~ImageSectionHeader() {
    delete [] kNameArr;
    delete [] kSizeArr;
    delete [] kCharsNumArr;
    delete [] kCharsValArr;
    delete [] name;
}

void ImageSectionHeader::print() const {
    printf("[SECTION HEADER - %s]\n", name);
    AbstractPEStruct::print();
    printCharacteristics();
    puts("");
}

size_t ImageSectionHeader::getNextAdrOfSectionHeader() const {
    return getInitialAdr() + getSize();
}

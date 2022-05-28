#include "imageDosStub.h"

ImageDosStub::ImageDosStub(TargetFile * const kFile, const size_t kInitialAdrOfNT)
: length_(kInitialAdrOfNT - kInitialAdr_) {
    sub_bin_ = new std::byte[length_];
    kFile->getFileContents(sub_bin_, kInitialAdr_, length_);
}

void ImageDosStub::print() const {
    const size_t k16xLen = length_ % 16
            ? 16 * (length_ / 16 + 1)
            : length_;

    if (sub_bin_ == nullptr) throw std::exception();

    puts("[IMAGE DOS STUB PROGRAM]");
    puts("- BYTES -");

    for (size_t i = 0; i < length_;) {
        const auto kHexNum = size_t(sub_bin_[i]);
        printf("%02zx%c", kHexNum, ++i % 16 ? ' ' : '\n');
    }

    printf("%s- ASCII -\n", length_ % 16 ? "\n" : "");

    for (size_t i = 0; i < k16xLen;) {
        const auto kUChr       = (unsigned char)sub_bin_[i];
        const char kHandledChr =
                i >= length_              ? ' '         :
                31 < kUChr && kUChr < 127 ? char(kUChr) :
                '.';

        if (!(i % 16)) printf("| ");
        printf("%c%s", kHandledChr, ++i % 16 ? " " : " |\n");
    }

    puts("");
}

ImageDosStub::~ImageDosStub() {
    delete [] sub_bin_;
}

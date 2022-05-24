#include "imageDosStub.h"

ImageDosStub::ImageDosStub(TargetFile & file, const size_t kInitialAdrOfNT)
: file_(file), length_(kInitialAdrOfNT - kInitialAdr_) {
    using std::byte;

    sub_bin_ = new byte[length_];
    file_.getFileContents(sub_bin_, kInitialAdr_, length_);
}

void ImageDosStub::print() {
    const size_t k16xLen = length_ % 16
            ? 16 * (length_ / 16 + 1)
            : length_;

    printf("[IMAGE DOS STUB PROGRAM]\n");

    printf("- BYTES -\n");
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

    printf("\n");
}

ImageDosStub::~ImageDosStub() {
    delete [] sub_bin_;
}

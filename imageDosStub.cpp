#include "imageDosStub.h"

ImageDosStub::ImageDosStub(TargetFile & file, const size_t kInitialAdrOfNT)
: file_(file), length_(kInitialAdrOfNT - kInitialAdr_) {
    using std::byte;

    sub_bin_ = new byte[length_];
    file_.getFileContents(sub_bin_, kInitialAdr_, length_);
}

void ImageDosStub::print() {
    printf("[IMAGE DOS STUB PROGRAM]\n");

    printf("- BYTES -\n");
    for (size_t i = 0; i < length_;) {
        const auto kHexNum = size_t(sub_bin_[i]);
        printf("%02zx%c", kHexNum, ++i % 16 ? ' ' : '\n');
    }

    printf("- ASCII -\n");
    for (size_t i = 0; i < length_;) {
        const auto kUChr       = (unsigned char)sub_bin_[i];
        const char kHandledChr = 33 <= kUChr && kUChr <= 126 ? char(kUChr) : ' ';

        printf("%s", i % 16 ? "" : "| ");
        printf("%c%s", kHandledChr, ++i % 16 ? "" : " |\n");
    }

    printf("\n");
}

ImageDosStub::~ImageDosStub() {
    delete [] sub_bin_;
}

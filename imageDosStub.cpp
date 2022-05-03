#include "imageDosStub.h"

ImageDosStub::ImageDosStub(TargetFile & file, const unsigned kInitialAdrOfNT)
: file_(file), length_(kInitialAdrOfNT - kInitialAdr_) {
    printf("NT : %u\n", kInitialAdrOfNT);
}

void ImageDosStub::print() {
    using std::byte;

    byte dos_stub[length_];
    printf("%u %u\n", kInitialAdr_, length_);
    file_.getFileContents(dos_stub, kInitialAdr_, length_); // debug

    for (unsigned i = length_; i; i--) {
        const unsigned kIdx = length_ - i;
        printf("%02x%c", unsigned(dos_stub[kIdx]), (kIdx + 1) % 16 ? ' ' : '\n');
    }
    printf("\n");

    for (unsigned i = length_; i; i--) {
        const unsigned kIdx  = length_ - i;
        const auto     kChr = (unsigned char)dos_stub[kIdx];
        printf("%c%c", 33 <= kChr && kChr <= 126 ? char(kChr) : ' ', (kIdx + 1) % 16 ? ' ' : '\n');
    }
    printf("\n");
}

#include "imageNtHeaders.h"

ImageNtHeaders::ImageNtHeaders(TargetFile * file, const size_t initial_adr)
: AbstractPEStruct(file, initial_adr, 1, kSzOfDWORD_) {
    using std::byte;
    using std::fill_n;

    const size_t kSize = getSize();

    auto value = new char[kSize];
    for (size_t i = 0; i < kSize; i++) {
        value[i] = char(sub_bin_[i]);
    }

    elem_info_->name = "Signature";
    elem_info_->size = kSzOfDWORD_;
    elem_info_->adr  = 0;
    elem_info_->val  = value;
}

void ImageNtHeaders::print() {
    printf("[IMAGE NT HEADERS]\n");

    AbstractPEStruct::print();

    printf("\n");
}

size_t ImageNtHeaders::getInitialAdrOfFileHd() const {
    return getInitialAdr() + getSize();
}

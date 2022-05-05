#include "imageNtHeaders.h"

ImageNtHeaders::ImageNtHeaders(TargetFile & file, const unsigned initial_adr)
: AbstractPEStruct(file, initial_adr, 1, kSzOfDWORD_) {
    using std::byte;
    using std::fill_n;

    const unsigned kSize = getSize();

    sub_bin_ = new byte[kSize];
    getFile().getFileContents(sub_bin_, getInitialAdr(), kSize);

    auto value = new char[kSize];
    for (unsigned i = kSize; i; i--) {
        const unsigned kIdx = kSize - i;
        value[kIdx] = char(sub_bin_[kIdx]);
    }

    elem_info_->name = "Signature";
    elem_info_->desc = "IMAGE NT SIGNATURE";
    elem_info_->size = kSzOfDWORD_;
    elem_info_->adr  = 0;
    elem_info_->val  = value;
}

void ImageNtHeaders::print() {
    AbstractPEStruct::print();
    printf("\n");
}

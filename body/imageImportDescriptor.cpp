#include "imageImportDescriptor.h"

const size_t ImageImportDescriptor::StructSize = 0x14;

ConstCString ImageImportDescriptor::getName(const size_t initialAdr) {
    const TargetFile * kFile = getFile();

    size_t length = 0;
    while(kFile->getFileContents(initialAdr + length++, 1));

    auto * name = new std::byte [length];
    kFile->getFileContents(name, initialAdr, length);

    return (const char *)name;
}

void ImageImportDescriptor::printIAT() const {
    for (const std::pair<const short, const char *> & kOrdNm : imp_by_nm_lst) {
        printf("%hx %s\n", kOrdNm.first, kOrdNm.second);
    }
}

ImageImportDescriptor::ImageImportDescriptor(
        TargetFile                 * const     kFile,
        const size_t                           kInitialAdr,
        std::list<std::pair<size_t, size_t>> * va_ptr2raw)
        : AbstractPEStruct(kFile, kInitialAdr, 5, StructSize) {
    auto size_arr = new size_t [kNumOfElem_] {};
    std::fill_n(size_arr, kNumOfElem_, kSzOfDWORD_);

    for (size_t i = 0, adr = 0; i < kNumOfElem_; adr += size_arr[i++]) {
        const size_t kSize    = size_arr[i],
                     kIsNotNm = i ^ 3;

        if (!kIsNotNm) {
            const size_t kNameAdr    = getSubBytes(sub_bin_, adr, kSize),
                         kNameAdrRaw = rvaToRaw(kNameAdr, va_ptr2raw);

            kImportedLibNm = (const char *)getName(kNameAdrRaw);
        }

        elem_info_[i].name = kNameArr_[i];
        elem_info_[i].size = kSize;
        elem_info_[i].adr  = adr;
        elem_info_[i].val  = kIsNotNm ? "" : kImportedLibNm;
    }

    delete [] size_arr;

    const size_t kPtrSzOfIIN = getIs32bit() ? kSzOfDWORD_ : kSzOfQWORD_,
                 kOFstThk    = getSubBytes(sub_bin_, elem_info_->adr, elem_info_->size);

    for (size_t o_thk_raw = rvaToRaw(kOFstThk, va_ptr2raw);; o_thk_raw += kPtrSzOfIIN) {

        const size_t kOrdinalPtr    = kFile->getFileContents(o_thk_raw, kPtrSzOfIIN);
        if (!kOrdinalPtr) break;

        const size_t kOrdinalPtrRaw = rvaToRaw(kOrdinalPtr, va_ptr2raw),
                     kNamePtrRaw    = kOrdinalPtrRaw + kSzOfWORD_;
        const auto   kOrdinal       = (const short)kFile->getFileContents(kOrdinalPtrRaw, kSzOfWORD_);

        imp_by_nm_lst.emplace_back(kOrdinal, getName(kNamePtrRaw));
    }
}

ImageImportDescriptor::~ImageImportDescriptor() {
    delete kImportedLibNm;
    delete [] kNameArr_;
    for (std::pair<const short, const char *> & elem : imp_by_nm_lst) {
        delete [] elem.second;
    }
}

void ImageImportDescriptor::print() const {
    printf("[IMAGE IMPORT DESCRIPTOR - %s]\n", kImportedLibNm);
    AbstractPEStruct::print();
    printIAT();
    puts("");
}

size_t ImageImportDescriptor::getNextIIDAdr() {
    return getInitialAdr() + getSize();
}

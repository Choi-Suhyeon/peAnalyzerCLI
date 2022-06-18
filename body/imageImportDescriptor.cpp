#include "imageImportDescriptor.h"

const size_t ImageImportDescriptor::StructSize_ = 0x14;

ConstCString ImageImportDescriptor::getName(const size_t initialAdr) {
    const TargetFile * kFile = getFile();

    size_t length = 0;
    while(kFile->getFileContents(initialAdr + length++, 1));

    auto * name = new std::byte [length];
    kFile->getFileContents(name, initialAdr, length);

    return (const char *)name;
}

void ImageImportDescriptor::printIAT() const {
    for (const auto & kOrdNm : imp_by_nm_lst_) {
        printf("%04hx %s\n", kOrdNm.first, kOrdNm.second);
    }
}

ImageImportDescriptor::ImageImportDescriptor(
        TargetFile    * const kFile,
        const size_t          kInitialAdr,
        SizeTPairList *       va_ptr2raw)
: AbstractPEStruct(kFile, kInitialAdr, 5, StructSize_) {
    auto size_arr = new size_t [kNumOfElem_] {};
    std::fill_n(size_arr, kNumOfElem_, kSzOfDWORD_);

    for (size_t i = 0, adr = 0; i < kNumOfElem_; adr += size_arr[i++]) {
        const size_t kSize    = size_arr[i],
                     kIsNotNm = i ^ 3;

        if (!kIsNotNm) {
            const size_t kNameAdr    = getSubBytes(sub_bin_, adr, kSize),
                         kNameAdrRaw = rvaToRaw(kNameAdr, va_ptr2raw);

            kImportedLibNm_ = (const char *)getName(kNameAdrRaw);
        }

        elem_info_[i].name = kNameArr_[i];
        elem_info_[i].size = kSize;
        elem_info_[i].adr  = adr;
        elem_info_[i].val  = kIsNotNm ? "" : kImportedLibNm_;
    }

    delete [] size_arr;
    delete [] kNameArr_;

    const size_t kOFstThk = getSubBytes(sub_bin_, elem_info_[0].adr, elem_info_[0].size),
                 kFstThk  = getSubBytes(sub_bin_, elem_info_[4].adr, elem_info_[4].size);

    first_thunk_ = rvaToRaw(kFstThk, va_ptr2raw);

    for (size_t o_thk_raw = rvaToRaw(kOFstThk, va_ptr2raw);; o_thk_raw += kPtrSzOfIIN_) {

        const size_t kOrdinalPtr    = kFile->getFileContents(o_thk_raw, kPtrSzOfIIN_);
        if (!kOrdinalPtr) break;

        const size_t kOrdinalPtrRaw = rvaToRaw(kOrdinalPtr, va_ptr2raw),
                     kNamePtrRaw    = kOrdinalPtrRaw + kSzOfWORD_;
        const auto   kOrdinal       = (const short)kFile->getFileContents(kOrdinalPtrRaw, kSzOfWORD_);

        imp_by_nm_lst_.emplace_back(kOrdinal, getName(kNamePtrRaw));
    }
}

ImageImportDescriptor::~ImageImportDescriptor() {
    delete kImportedLibNm_;
    for (auto & elem : imp_by_nm_lst_) {
        delete [] elem.second;
    }
}

void ImageImportDescriptor::print() const {
    printf("[IMAGE IMPORT DESCRIPTOR - %s]\n", kImportedLibNm_);
    AbstractPEStruct::print();
    printIAT();
    puts("");
}

size_t ImageImportDescriptor::getNextIIDAdr() {
    return getInitialAdr() + getSize();
}

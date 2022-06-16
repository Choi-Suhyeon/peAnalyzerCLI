#include "imageImportDescriptor.h"

ImageImportDescriptor::ImageImportDescriptor(
        TargetFile * const     kFile,
        const size_t           kInitialAdr,
        std::list<SizeTPair> * va_ptr2raw)
: AbstractPEStruct(kFile, kInitialAdr, 5, 0x14) {
    auto size_arr = new size_t [kNumOfElem_] {};
    std::fill_n(size_arr, kNumOfElem_, kSzOfDWORD_);

    for (size_t i = 0, adr = 0; i < kNumOfElem_; adr += size_arr[i++]) {
        const size_t kSize    = size_arr[i],
                     kIsNotNm = i ^ 3;

        if (!kIsNotNm) {
            char * name_adr = (char *)rvaToRaw(getSubBytes(sub_bin_, adr, kSize), va_ptr2raw);
            size_t length   = 0;

            while(*(char *)(name_adr + length++));
            kImportedObjNm = new char [length];
            memcpy((void *) kImportedObjNm, name_adr, length);
        }

        elem_info_[i].name = kNameArr_[i];
        elem_info_[i].size = kSize;
        elem_info_[i].adr  = adr;
        elem_info_[i].val  = kIsNotNm ? "" : kImportedObjNm;
    }
}

ImageImportDescriptor::~ImageImportDescriptor() {
    delete kImportedObjNm;
    delete [] kNameArr_;
}

void ImageImportDescriptor::print() const {
    printf("[IMAGE IMPORT DESCRIPTOR - %s]\n", kImportedObjNm);
    AbstractPEStruct::print();
    puts("");
}

size_t ImageImportDescriptor::getNextIIDAdr() {
    return getInitialAdr() + getSize();
}

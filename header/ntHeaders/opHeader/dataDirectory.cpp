#include "dataDirectory.h"

DataDirectory::DataDirectory(TargetFile * const kFile, const size_t kInitialAdr)
: AbstractPEStruct(kFile, kInitialAdr, 32, 0x80) {
    for (size_t i = 0, current_adr = 0; i < getNumOfElem(); i++, current_adr += kSzOfDWORD_) {
        const size_t kIsOdd  = i & 1,
                     kValIdx = i >> 1;

        elem_info_[i].name = kIsOdd ? "Size" : "RVA";
        elem_info_[i].size = kSzOfDWORD_;
        elem_info_[i].adr  = current_adr;
        elem_info_[i].val  = !(kIsOdd | (kValIdx >= kNumOfVal_))
                ? kValArr_[kValIdx]
                : "";
    }
}

DataDirectory::~DataDirectory() {
    delete [] kValArr_;
}

void DataDirectory::print() const {
    puts("[DATA Directory]");
    AbstractPEStruct::print();
    puts("");
}

size_t DataDirectory::getInitialAdrOfSectionHeader() const {
    return getInitialAdr() + getSize();
}
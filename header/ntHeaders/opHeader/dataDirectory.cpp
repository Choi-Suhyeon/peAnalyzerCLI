#include "dataDirectory.h"

DataDirectory::DataDirectory(TargetFile * file, size_t initial_adr)
: AbstractPEStruct(file, initial_adr, 32, 0x80) {
    for (size_t i = 0, current_adr = 0; i < getNumOfElem(); i++, current_adr += kSzOfDWORD_) {
        const size_t kIsOdd  = i & 1,
                     kValIdx = i >> 1;

        elem_info_[i].name = kIsOdd ? "Size" : "RVA";
        elem_info_[i].size = kSzOfDWORD_;
        elem_info_[i].adr  = current_adr;
        elem_info_[i].val  = !(kIsOdd | (kValIdx >= kNumOfVal))
                ? kValArr[kValIdx]
                : "";
    }
}

void DataDirectory::print() {
    puts("[DATA Directory]");
    AbstractPEStruct::print();
    puts("");
}

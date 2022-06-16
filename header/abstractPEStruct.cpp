#include "abstractPEStruct.h"

const size_t AbstractPEStruct::kSzOfBYTE_  = 1,
             AbstractPEStruct::kSzOfWORD_  = 2,
             AbstractPEStruct::kSzOfDWORD_ = 4,
             AbstractPEStruct::kSzOfQWORD_ = 8;

AbstractPEStruct::AbstractPEStruct(
        TargetFile * const kFile,
        const size_t       kInitialAdr,
        const size_t       kNumOfElem,
        const size_t       kSize)
: initial_adr_(kInitialAdr), num_of_elem_(kNumOfElem), size_(kSize), file_(kFile) {
    elem_info_ = new ElementDetails_[kSize];
    sub_bin_   = new std::byte[kSize];
    is_32bit_  = file_->getIs32bit();
    file_->getFileContents(sub_bin_, getInitialAdr(), kSize);
}

AbstractPEStruct::~AbstractPEStruct() {
    delete [] elem_info_;
    delete [] sub_bin_;
}

void AbstractPEStruct::print() const {
    const bool   kIs32bit     = getIs32bit();
    const char * kTitleFormat = kIs32bit
            ? "%8s%s | %17s%13s | %4s | %6s%2s | %10s\n"
            : "%11s%5s | %17s%13s | %4s | %10s%6s | %10s\n";
    const char * kTableFormat = kIs32bit
            ? "%08.8zX | %-30s | %4zu | %8.8s | %s\n"
            : "%016.16zX | %-30s | %4zu | %16.16s | %s\n";

    printf(kTitleFormat, "RVA&RAW", "", "NAME", "", "SIZE", "DATA", "", "VALUE");

    for (size_t i = 0; i < num_of_elem_; i++) {
        const size_t kSize        = elem_info_[i].size,
                     kAdr         = elem_info_[i].adr + initial_adr_,
                     kData        = getSubBytes(sub_bin_, kAdr, kSize),
                     kSzOfDataStr = kSize * 2;

        char * data_str    = new char [kSzOfDataStr + 1];
        char * interim_str = new char [kSzOfDataStr + 1];

        std::fill_n(data_str, kSzOfDataStr, '0');
        sprintf(interim_str, "%zX", kData);
        strcpy(data_str + kSzOfDataStr - strlen(interim_str), interim_str);
        delete [] interim_str;

        printf(kTableFormat, kAdr, elem_info_[i].name, kSize, data_str, elem_info_[i].val);

        delete [] data_str;
    }
}

size_t       AbstractPEStruct::getInitialAdr() const { return initial_adr_; }
size_t       AbstractPEStruct::getNumOfElem()  const { return num_of_elem_; }
size_t       AbstractPEStruct::getSize()       const { return size_; }
bool         AbstractPEStruct::getIs32bit()    const { return is_32bit_; }
TargetFile * AbstractPEStruct::getFile()             { return file_; }

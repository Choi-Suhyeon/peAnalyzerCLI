#include "abstractPEStruct.h"

const size_t AbstractPEStruct::kSzOfBYTE_  = 1,
             AbstractPEStruct::kSzOfWORD_  = 2,
             AbstractPEStruct::kSzOfDWORD_ = 4,
             AbstractPEStruct::kSzOfQWORD_ = 8;

AbstractPEStruct::AbstractPEStruct(TargetFile & file, size_t initial_adr, size_t num_of_elem, size_t size)
: initial_adr_(initial_adr), num_of_elem_(num_of_elem), size_(size), file_(file) {
    using std::byte;

    elem_info_ = new ElementDetails_[size_];
    sub_bin_   = new byte[size_];
    file_.getFileContents(sub_bin_, getInitialAdr(), size_);
}

AbstractPEStruct::~AbstractPEStruct() {
    delete [] elem_info_;
    delete [] sub_bin_;
}

void AbstractPEStruct::print() {
    const bool   kIs32bit     = getIs32bit();
    const char * kTitleFormat = kIs32bit
            ? "%8s%s | %17s%13s | %4s | %6s%2s | %10s\n"
            : "%11s%5s | %17s%13s | %4s | %10s%6s | %10s\n";
    const char * kTableFormat = kIs32bit
            ? "%08zX | %-30s | %4zu | %8zX | %s\n"
            : "%016zX | %-30s | %4zu | %16zX | %s\n";

    printf(kTitleFormat, "ADDRESS", "", "NAME", "", "SIZE", "DATA", "", "VALUE");

    for (size_t i = 0; i < num_of_elem_; i++) {
        const size_t kAdr  = elem_info_[i].adr,
                     kSize = elem_info_[i].size,
                     kData = TargetFile::getSubBytes(sub_bin_, kAdr, kSize);

        printf(kTableFormat, kAdr, elem_info_[i].name, kSize, kData, elem_info_[i].val);
    }
}

size_t       AbstractPEStruct::getInitialAdr() const { return initial_adr_; }
size_t       AbstractPEStruct::getNumOfElem()  const { return num_of_elem_; }
size_t       AbstractPEStruct::getSize()       const { return size_; }
bool         AbstractPEStruct::getIs32bit()          { return file_.getIs32bit(); }
TargetFile & AbstractPEStruct::getFile()             { return file_; }

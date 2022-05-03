#include "abstractPEStruct.h"

const unsigned AbstractPEStruct::kSzOfBYTE_  = 1;
const unsigned AbstractPEStruct::kSzOfWORD_  = 2;
const unsigned AbstractPEStruct::kSzOfDWORD_ = 4;
const unsigned AbstractPEStruct::kSzOfQWORD_ = 8;
const unsigned AbstractPEStruct::kSzOfAdr32_ = kSzOfDWORD_;
const unsigned AbstractPEStruct::kSzOfAdr64_ = kSzOfQWORD_;

AbstractPEStruct::AbstractPEStruct(TargetFile & file, unsigned initial_adr, unsigned num_of_elem, unsigned size):
        initial_adr_(initial_adr),
        num_of_elem_(num_of_elem),
        size_(size),
        file_(file) {
    elem_info_ = new ElementDetails_[size_];
}

AbstractPEStruct::~AbstractPEStruct() {
    delete [] elem_info_;
    delete [] sub_bin_;
}

void AbstractPEStruct::print() {
    using std::hex;
    using std::cout;
    using std::endl;

    for (unsigned i = 0; i < num_of_elem_; i++) {
        unsigned adr;
        if (getIs32bit()) adr = changeBytesToUnsigned(elem_info_[i].adr.bit32, 4);
        else              adr = changeBytesToUnsigned(elem_info_[i].adr.bit64, 8);

        cout << "adr : " << hex << adr << endl;
        cout << "name : " << elem_info_[i].name << endl;
        cout << "size : " << elem_info_[i].size << endl;
        cout << "desc : " << elem_info_[i].desc << endl;
        cout << "data : " << TargetFile::getSubBytes(sub_bin_, adr, elem_info_[i].size) << endl;
        cout << "val : "  << elem_info_[i].val << endl;
        cout << endl;
    }
}

unsigned     AbstractPEStruct::getInitialAdr() const { return initial_adr_; }
unsigned     AbstractPEStruct::getNumOfElem()  const { return num_of_elem_; }
unsigned     AbstractPEStruct::getSize()       const { return size_; }
bool         AbstractPEStruct::getIs32bit()          { return file_.getIs32bit(); }
TargetFile & AbstractPEStruct::getFile()             { return file_; }

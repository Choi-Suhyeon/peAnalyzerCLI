#include "abstractPEStruct.h"

AbstractPEStruct::AbstractPEStruct(TargetFile & file, unsigned initial_adr, unsigned num_of_elem, unsigned size):
        initial_adr_(initial_adr),
        num_of_elem_(num_of_elem),
        size_(size),
        file_(file) {
    elem_info_ = new ElementDetails_[size_];
}

AbstractPEStruct::~AbstractPEStruct() {
    delete [] elem_info_;
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
        cout << "data : " << file_.getFileContents(adr, elem_info_[i].size) << endl;
        cout << "val : "  << elem_info_[i].val << endl;
        cout << endl;
    }
}

unsigned     AbstractPEStruct::getSzOfBYTE()         { return kSzOfBYTE; }
unsigned     AbstractPEStruct::getSzOfWORD()         { return kSzOfWORD; }
unsigned     AbstractPEStruct::getSzOfDWORD()        { return kSzOfDWORD; }
unsigned     AbstractPEStruct::getSzOfQWORD()        { return kSzOfQWORD; }
unsigned     AbstractPEStruct::getSzOfAdr32()        { return kSzOfAdr32; }
unsigned     AbstractPEStruct::getSzOfAdr64()        { return kSzOfAdr64; }
unsigned     AbstractPEStruct::getInitialAdr() const { return initial_adr_; }
unsigned     AbstractPEStruct::getNumOfElem()  const { return num_of_elem_; }
unsigned     AbstractPEStruct::getSize()       const { return size_; }
bool         AbstractPEStruct::getIs32bit()          { return file_.check32bit(); }
TargetFile & AbstractPEStruct::getFile()             { return file_; }

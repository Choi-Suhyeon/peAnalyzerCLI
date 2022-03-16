#include "targetFile.h"

TargetFile::TargetFile(const std::string & file_name) {
     using std::ios;
     using std::ifstream;

     tgt_file_ = ifstream(file_name, ios::in | ios::binary);
}

TargetFile::TargetFile(TargetFile & file) {
    using std::move;

    tgt_file_ = move(file.tgt_file_);
}

TargetFile::~TargetFile() {
    tgt_file_.close();
}

void TargetFile::getFileContents(std::byte result[], const unsigned initial_pos, const unsigned size) {
    using std::ios;

    tgt_file_.seekg(initial_pos, ios::beg);
    tgt_file_.read(reinterpret_cast<char *>(result), size);
}

unsigned TargetFile::getFileContents(const unsigned initial_pos, const unsigned size) {
    using std::byte;

    byte interim[size];
    getFileContents(interim, initial_pos, size);

    return changeBytesToUnsigned(interim, size);
}

bool TargetFile::check32bit() {
    using std::ios;
    using std::byte;

    const unsigned kPosELfanew    = 0x3C;
    const unsigned kBysOfSzOfOpHd = 2;
    const unsigned kPosSzOfOpHd   = 0x14;
    const unsigned kSz32Bit       = 0xE0;
    const unsigned kSz64bit       = 0xF0;

    byte e_lfanew[4];
    getFileContents(e_lfanew, kPosELfanew, sizeof e_lfanew);

    const unsigned kUELfanew = changeBytesToUnsigned(e_lfanew, sizeof e_lfanew);

    byte sz_of_op_hd[kBysOfSzOfOpHd];
    getFileContents(sz_of_op_hd, kUELfanew + kBysOfSzOfOpHd, sizeof sz_of_op_hd);

    const unsigned kUSzOfOpHd = changeBytesToUnsigned(sz_of_op_hd, sizeof sz_of_op_hd);

    const bool kIs32Or64 = kUSzOfOpHd == kSz32Bit || kUSzOfOpHd == kSz64bit;
    if (kIs32Or64) return kUSzOfOpHd == kSz32Bit;
    else           throw  std::exception();
}

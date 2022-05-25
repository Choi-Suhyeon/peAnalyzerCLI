#include "targetFile.h"

TargetFile::TargetFile(const std::string & file_name) {
    using std::ios;
    using std::byte;
    using std::ifstream;
    using std::exception;
    using std::streamsize;

    const size_t kSz32Bit = 0xE0,
                 kSz64bit = 0xF0;

    ifstream tgt_file_(file_name, ios::in | ios::binary);
    if (!tgt_file_.is_open()) throw exception();

    tgt_file_.seekg(0, ios::end);
    whole_bin_ = new byte[sz_ = tgt_file_.tellg()];
    tgt_file_.seekg(0, ios::beg);
    tgt_file_.read((char *)whole_bin_, streamsize(sz_));
    tgt_file_.close();

    const size_t kAdrOfSzOfOpHd = bytesToSizeT(whole_bin_ + 0x3C, 4) + 0x14,
                 kSzOfOpHd      = bytesToSizeT(whole_bin_ + kAdrOfSzOfOpHd, 2);

    if (!((is_32bit_ = !(kSzOfOpHd ^ kSz32Bit)) | !(kSzOfOpHd ^ kSz64bit))) throw exception();
}

TargetFile::~TargetFile() {
    delete [] whole_bin_;
}

void TargetFile::getFileContents(std::byte * const result, const size_t initial_pos, const size_t size) const {
    getSubBytes(result, whole_bin_, initial_pos, size);
}

unsigned TargetFile::getFileContents(const size_t initial_pos, const size_t size) const {
    return getSubBytes(whole_bin_, initial_pos, size);
}

bool TargetFile::getIs32bit() const { return is_32bit_; }

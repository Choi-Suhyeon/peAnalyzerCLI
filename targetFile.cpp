#include "targetFile.h"

void TargetFile::getSubBytes(
              std::byte * const result,
        const std::byte * const bins,
        const unsigned          initial_pos,
        const unsigned          size) {
    using std::exception;

    if (!bins) throw exception();
    memmove(result, bins + initial_pos, size);
}

unsigned TargetFile::getSubBytes(
        const std::byte * const bins,
        const unsigned          initial_pos,
        const unsigned          size) {
    using std::byte;

    byte interim[size];
    getSubBytes(interim, bins, initial_pos, size);

    return changeBytesToUnsigned(interim, size);
}

TargetFile::TargetFile(const std::string & file_name) {
    using std::ios;
    using std::byte;
    using std::ifstream;
    using std::exception;

    const unsigned kSz32Bit = 0xE0;
    const unsigned kSz64bit = 0xF0;

    ifstream tgt_file_(file_name, ios::in | ios::binary);
    if (!tgt_file_.is_open()) {
        throw exception();
    }

    tgt_file_.seekg(0, ios::end);
    whole_bin_ = new byte[sz_ = tgt_file_.tellg()];
    tgt_file_.seekg(0, ios::beg);
    tgt_file_.read((char *)whole_bin_, sz_);
    tgt_file_.close();

    const unsigned kAdrOfSzOfOpHd = changeBytesToUnsigned(whole_bin_ + 0x3C, 4) + 0x14;
    const unsigned kSzOfOpHd      = changeBytesToUnsigned(whole_bin_ + kAdrOfSzOfOpHd, 2);

    if (!((is_32bit_ = kSzOfOpHd == kSz32Bit) || kSzOfOpHd == kSz64bit)) throw exception();
}

/*
TargetFile::TargetFile(TargetFile & file) {
    memmove(whole_bin_, file.whole_bin_, file.sz_);
    is_32bit_ = file.is_32bit_;
}
 */

TargetFile::~TargetFile() {
    // delete [] whole_bin_;
}

void TargetFile::getFileContents(std::byte * const result, const unsigned initial_pos, const unsigned size) const {
    getSubBytes(result, whole_bin_, initial_pos, size);
}

unsigned TargetFile::getFileContents(const unsigned initial_pos, const unsigned size) const {
    return getSubBytes(whole_bin_, initial_pos, size);
}

bool TargetFile::getIs32bit() const { return is_32bit_; }

#ifndef PEANALCLI_TARGETFILE_H
#define PEANALCLI_TARGETFILE_H

#include "byte.h"
#include <fstream>
#include <memory>


class TargetFile {
    std::byte * whole_bin_ = nullptr;

    bool     is_32bit_ = false;
    unsigned sz_       = 0;

public:
    static void     getSubBytes(std::byte *, const std::byte *, unsigned, unsigned);
    static unsigned getSubBytes(const std::byte *, unsigned, unsigned);

    explicit TargetFile(const std::string &);
    // TargetFile(TargetFile &);
    ~TargetFile();

                  void     getFileContents(std::byte *, unsigned, unsigned) const;
    [[nodiscard]] unsigned getFileContents(unsigned, unsigned) const;
    [[nodiscard]] bool     getIs32bit() const;
};

#endif //PEANALCLI_TARGETFILE_H

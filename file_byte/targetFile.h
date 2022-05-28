#ifndef PEANALCLI_TARGETFILE_H
#define PEANALCLI_TARGETFILE_H

#include "byte.h"
#include <fstream>
#include <memory>

class TargetFile {
    std::byte * whole_bin_ = nullptr;
    bool        is_32bit_  = false;
    size_t      sz_        = 0;

public:
    explicit TargetFile(const char *);
    ~TargetFile();

                  void     getFileContents(std::byte *, size_t, size_t) const;
    [[nodiscard]] size_t   getFileContents(size_t, size_t) const;
    [[nodiscard]] bool     getIs32bit() const;
};

#endif //PEANALCLI_TARGETFILE_H

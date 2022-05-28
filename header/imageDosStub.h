#ifndef PEANALCLI_IMAGEDOSSTUB_H
#define PEANALCLI_IMAGEDOSSTUB_H

#import "../file_byte/targetFile.h"

class ImageDosStub {
    const size_t kInitialAdr_ = 0x40;

    std::byte * sub_bin_ = nullptr;
    size_t      length_  = 0;

public:
    ImageDosStub(TargetFile *, size_t);
    ~ImageDosStub();

    void print() const;
};

#endif //PEANALCLI_IMAGEDOSSTUB_H

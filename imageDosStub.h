#ifndef PEANALCLI_IMAGEDOSSTUB_H
#define PEANALCLI_IMAGEDOSSTUB_H

#import "targetFile.h"
#import <cstdio>

class ImageDosStub {
    const size_t kInitialAdr_ = 0x40;

    TargetFile  file_;
    size_t      length_;
    std::byte * sub_bin_;

public:
    ImageDosStub(TargetFile &, size_t);
    ~ImageDosStub();

    void print();
};

#endif //PEANALCLI_IMAGEDOSSTUB_H

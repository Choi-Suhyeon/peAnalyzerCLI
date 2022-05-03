#ifndef PEANALCLI_IMAGEDOSSTUB_H
#define PEANALCLI_IMAGEDOSSTUB_H

#import "targetFile.h"
#import <cstdio>

class ImageDosStub {
    const unsigned kInitialAdr_ = 0x40;

    TargetFile file_;
    unsigned   length_;

public:
    ImageDosStub(TargetFile &, unsigned);

    void print();
};

#endif //PEANALCLI_IMAGEDOSSTUB_H

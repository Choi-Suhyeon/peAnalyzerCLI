#ifndef PEANALCLI_IMAGENTHEADERS_H
#define PEANALCLI_IMAGENTHEADERS_H

#import "../abstractPEStruct.h"

class ImageNtHeaders final: protected AbstractPEStruct {
public:
    explicit ImageNtHeaders(TargetFile *, size_t);

    void print() final;

    [[nodiscard]] size_t getInitialAdrOfFileHd() const;
};

#endif //PEANALCLI_IMAGENTHEADERS_H

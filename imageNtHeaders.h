#ifndef PEANALCLI_IMAGENTHEADERS_H
#define PEANALCLI_IMAGENTHEADERS_H

#import "abstractPEStruct.h"

class ImageNtHeaders: protected AbstractPEStruct {
public:
    explicit ImageNtHeaders(TargetFile &, unsigned);

    void print() final;

    [[nodiscard]] unsigned getInitialAdrOfFileHd() const { return getInitialAdr() + getSize(); }
};

#endif //PEANALCLI_IMAGENTHEADERS_H

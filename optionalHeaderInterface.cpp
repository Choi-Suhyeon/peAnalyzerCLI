#include "optionalHeaderInterface.h"

char * OptionalHeaderInterface::getValOfMagic(const size_t data) const {
    switch (data) {
        case 0x10B: return (char *)kMagicArr[0];
        case 0x20B: return (char *)kMagicArr[1];
        default:    return (char *)"";
    }
}

char * OptionalHeaderInterface::getValOfSubSys(const size_t data) const {
    return (char *)(data < kNumSubSys ? kSubSysArr[data] : "");
}

OptionalHeaderInterface::~OptionalHeaderInterface() {
    delete [] kMagicArr;
    delete [] kSubSysArr;
}

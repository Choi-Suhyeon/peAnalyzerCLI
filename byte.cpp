#include "byte.h"

void switchLittleBig(std::byte adr[], const unsigned size) {
    using std::reverse;

    reverse(adr, adr + size);
}

unsigned changeBytesToUnsigned(const std::byte bytes[], const unsigned size) {
    using std::byte;
    using std::to_integer;

    const unsigned kHex         = 0x10;
    const unsigned kNumOfDigits = 2;

    unsigned result = 0;
    for (unsigned i = 0; i < size; i++) {
        result += unsigned(bytes[i]) * unsigned(pow(kHex, kNumOfDigits * i));
    }

    return result;
}

void changeUnsignedToBytes(const unsigned num, std::byte bytes[], const unsigned size) {
    using std::byte;
    using std::fill_n;

    const unsigned kBitsOfBy = 0xFF;

    fill_n(bytes, size, byte(0));

    unsigned interim = num;
    for (unsigned i = 0; i < size; i++) {
        bytes[i] = byte(interim % kBitsOfBy);

        if ((interim = num / kBitsOfBy) < kBitsOfBy) {
            bytes[i + 1] = byte(interim);
            break;
        }
    }
}
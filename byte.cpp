#include "byte.h"

void switchLittleBig(std::byte adr[], const size_t size) {
    using std::reverse;

    reverse(adr, adr + size);
}

size_t bytesToSizeT(const std::byte bytes[], const size_t size) {
    size_t result = 0;
    for (size_t i = 0; i < size; i++) {
        result += size_t(bytes[i]) * size_t(pow(0x10, i << 1));
    }

    return result;
}

void sizeTToBytes(const size_t num, std::byte bytes[], const size_t size) {
    using std::byte;

    memset(bytes, 0, size);

    size_t interim = num;
    for (size_t i = 0; i < size; i++) {
        bytes[i] = byte(interim % 0xFF);

        if ((interim = num / 0xFF) < 0xFF) {
            bytes[i + 1] = byte(interim);
            break;
        }
    }
}
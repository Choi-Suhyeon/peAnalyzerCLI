#include "byte.h"

void switchLittleBig(std::byte * const kAdr, const size_t kSize) {
    std::reverse(kAdr, kAdr + kSize);
}

size_t bytesToSizeT(const std::byte * const kBytes, const size_t kSize) {
    size_t result = 0;

    for (size_t i = 0; i < kSize; i++) {
        result += size_t(kBytes[i]) * size_t(pow(0x10, i << 1));
    }

    return result;
}

void sizeTToBytes(const size_t kNum, std::byte bytes[], const size_t kSize) {
    using std::byte;

    size_t interim = kNum;

    memset(bytes, 0, kSize);

    for (size_t i = 0; i < kSize; i++) {
        bytes[i] = byte(interim % 0xFF);

        if ((interim = kNum / 0xFF) < 0xFF) {
            bytes[i + 1] = byte(interim);
            break;
        }
    }
}

void getSubBytes(
        std::byte *       const kResult,
        const std::byte * const kBins,
        const size_t            kInitialPos,
        const size_t            kSize) {
    if (!kBins) throw std::exception();
    memmove(kResult, kBins + kInitialPos, kSize);
}

size_t getSubBytes(
        const std::byte * const kBins,
        const size_t            kInitialPos,
        const size_t            kSize) {
    std::byte interim[kSize];
    getSubBytes(interim, kBins, kInitialPos, kSize);

    return bytesToSizeT(interim, kSize);
}

size_t rvaToRaw(const size_t kRva, std::list<SizeTPair> * va_ptr2raw) {
    SizeTPair pre_elem = va_ptr2raw->front();

    for (auto & iter : *va_ptr2raw) {
        if (kRva > pre_elem.first & kRva < iter.second) break;
        pre_elem = iter;
    }

    return pre_elem.second + kRva - pre_elem.first;
}
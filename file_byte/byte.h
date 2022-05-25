#ifndef PEANALCLI_BYTE_H
#define PEANALCLI_BYTE_H

#include <algorithm>
#include <memory>
#include <cmath>

void   switchLittleBig(std::byte *, size_t);
size_t bytesToSizeT(const std::byte *, size_t size);
void   sizeTToBytes(size_t, std::byte *, size_t size);
void   getSubBytes(std::byte *, const std::byte *, size_t, size_t);
size_t getSubBytes(const std::byte *, size_t, size_t);

#endif //PEANALCLI_BYTE_H

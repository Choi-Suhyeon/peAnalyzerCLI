#ifndef PEANALCLI_BYTE_H
#define PEANALCLI_BYTE_H

#include "../redefType.h"
#include <algorithm>
#include <memory>
#include <cmath>
#include <list>

USING_PARTICULAR_TYPE

void   switchLittleBig(std::byte *, size_t);
size_t bytesToSizeT(const std::byte *, size_t size);
void   sizeTToBytes(size_t, std::byte *, size_t size);
void   getSubBytes(std::byte *, const std::byte *, size_t, size_t);
size_t getSubBytes(const std::byte *, size_t, size_t);
size_t rvaToRaw(size_t, std::list<SizeTPair> *);

#endif //PEANALCLI_BYTE_H

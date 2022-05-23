#ifndef PEANALCLI_BYTE_H
#define PEANALCLI_BYTE_H

#include <algorithm>
#include <memory>
#include <cmath>

void   switchLittleBig(std::byte [], size_t);
size_t bytesToSizeT(const std::byte bytes[], size_t size);
void   sizeTToBytes(size_t num, std::byte bytes[], size_t size);

#endif //PEANALCLI_BYTE_H

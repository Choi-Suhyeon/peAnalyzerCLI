#ifndef PEANALCLI_BYTE_H
#define PEANALCLI_BYTE_H

#import <algorithm>
#import <cmath>

void     switchLittleBig(std::byte [], unsigned);
unsigned changeBytesToUnsigned(const std::byte [], unsigned);
void     changeUnsignedToBytes(unsigned, std::byte bytes[], unsigned size);

#endif //PEANALCLI_BYTE_H

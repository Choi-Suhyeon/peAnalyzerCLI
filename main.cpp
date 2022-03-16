#include "imageDosHeader.h"

int main() {
    auto tf  = TargetFile("/Users/choisuhyeon/Desktop/CTFLab/dreamhack 2/chall9.exe");
    auto idh = ImageDosHeader(tf, 0);

    idh.print();

    return 0;
}


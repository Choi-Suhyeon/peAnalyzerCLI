#include "imageDosHeader.h"
#include "imageNtHeaders.h"
#include "imageDosStub.h"

int main() {
    auto tf  = TargetFile("/Users/choisuhyeon/Desktop/CTFLab/dreamhack 2/chall9.exe");
    auto idh = ImageDosHeader(tf, 0);
    auto ids = ImageDosStub(tf, idh.getInitialAdrOfNTHd());
    auto inh = ImageNtHeaders(tf, idh.getInitialAdrOfNTHd());

    idh.print();
    ids.print();
    inh.print();

    return 0;
}


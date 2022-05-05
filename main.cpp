#include "imageDosHeader.h"
#include "imageNtHeaders.h"
#include "imageFileHeader.h"
#include "imageDosStub.h"

int main() {
    auto tf  = TargetFile("/Users/choisuhyeon/Desktop/CTFLab/dreamhack 2/chall9.exe");
    auto idh = ImageDosHeader(tf, 0);
    auto ids = ImageDosStub(tf, idh.getInitialAdrOfNTHd());
    auto inh = ImageNtHeaders(tf, idh.getInitialAdrOfNTHd());
    auto ifh = ImageFileHeader(tf, inh.getInitialAdrOfFileHd());

    idh.print();
    ids.print();
    inh.print();
    ifh.print();

    return 0;
}


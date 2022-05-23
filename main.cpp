#include "imageDosHeader.h"
#include "imageNtHeaders.h"
#include "imageFileHeader.h"
#include "imageOptionalHeader32.h"
#include "imageDosStub.h"

int main() {
    char x86file[] = "/Users/choisuhyeon/Desktop/CTFLab/dreamhack 2/PEview.exe";
    char x64file[] = "/Users/choisuhyeon/Desktop/CTFLab/dreamhack 2/chall9.exe";

    auto tf  = new TargetFile(x86file);
    auto idh = new ImageDosHeader(*tf, 0);
    auto ids = new ImageDosStub(*tf, idh->getInitialAdrOfNTHd());
    auto inh = new ImageNtHeaders(*tf, idh->getInitialAdrOfNTHd());
    auto ifh = new ImageFileHeader(*tf, inh->getInitialAdrOfFileHd());
    auto ioh = new ImageOptionalHeader32(*tf, ifh->getInitialAdrOfOpHd());

    idh->print();
    ids->print();
    inh->print();
    ifh->print();
    ioh->print();

    return 0;
}


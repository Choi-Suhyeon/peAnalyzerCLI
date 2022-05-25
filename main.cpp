#include "header/imageDosHeader.h"
#include "header/ntHeaders/imageNtHeaders.h"
#include "header/ntHeaders/imageFileHeader.h"
#include "header/ntHeaders/opHeader/imageOptionalHeader32.h"
#include "header/ntHeaders/opHeader/imageOptionalHeader64.h"
#include "header/ntHeaders/opHeader/dataDirectory.h"
#include "header/imageDosStub.h"

int main() {
    char x86file[] = "/Users/choisuhyeon/Desktop/CTFLab/dreamhack 2/PEview.exe";
    char x64file[] = "/Users/choisuhyeon/Desktop/CTFLab/dreamhack 2/chall9.exe";

    auto tf  = new TargetFile(x86file);
    auto idh = ImageDosHeader(tf, 0);
    auto ids = ImageDosStub(tf, idh.getInitialAdrOfNTHd());
    auto inh = ImageNtHeaders(tf, idh.getInitialAdrOfNTHd());
    auto ifh = ImageFileHeader(tf, inh.getInitialAdrOfFileHd());
    auto ioh = ImageOptionalHeader32(tf, ifh.getInitialAdrOfOpHd());
    auto idd = DataDirectory(tf, ioh.getInitialAdrOfDataDir());
    delete tf;

    idh.print();
    ids.print();
    inh.print();
    ifh.print();
    ioh.print();
    idd.print();
    // header ntHeaders opHeader
    return 0;
}


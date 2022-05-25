#include "imageDosHeader.h"
#include "imageNtHeaders.h"
#include "imageFileHeader.h"
#include "imageOptionalHeader32.h"
#include "imageOptionalHeader64.h"
#include "dataDirectory.h"
#include "imageDosStub.h"

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
    /*
    delete ioh;
    delete ifh;
    delete inh;
    delete ids;
    delete idh;*/
    return 0;
}


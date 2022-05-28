#include "header/imageDosHeader.h"
#include "header/ntHeaders/imageNtHeaders.h"
#include "header/ntHeaders/imageFileHeader.h"
#include "header/ntHeaders/opHeader/imageOptionalHeader32.h"
#include "header/ntHeaders/opHeader/imageOptionalHeader64.h"
#include "header/ntHeaders/opHeader/dataDirectory.h"
#include "header/imageSectionHeader.h"
#include "header/imageDosStub.h"

#include <list>

std::list<ImageSectionHeader> getScnHeaders(TargetFile * file, size_t numOfScn, size_t initial_adr) {
    auto result = std::list<ImageSectionHeader>();

    while (numOfScn--) {
        result.emplace_back(file, initial_adr);
        initial_adr = result.back().getNextAdrOfSectionHeader();
    }

    return result;
}

void printScnHeaders(const std::list<ImageSectionHeader> & kScnHeaders) {
    for (const ImageSectionHeader & kScnHd : kScnHeaders) kScnHd.print();
}

int main() {
    using std::list;

    char x86file[] = "/Users/choisuhyeon/Desktop/CTFLab/dreamhack 2/PEview.exe";
    char x64file[] = "/Users/choisuhyeon/Desktop/CTFLab/dreamhack 2/chall9.exe";

    auto tf  = new TargetFile(x86file);
    auto idh = ImageDosHeader(tf, 0);
    auto ids = ImageDosStub(tf, idh.getInitialAdrOfNTHd());
    auto inh = ImageNtHeaders(tf, idh.getInitialAdrOfNTHd());
    auto ifh = ImageFileHeader(tf, inh.getInitialAdrOfFileHd());
    auto ioh = ImageOptionalHeader32(tf, ifh.getInitialAdrOfOpHd());
    auto idd = DataDirectory(tf, ioh.getInitialAdrOfDataDir());
    auto ish_lst = getScnHeaders(tf,
                                 ifh.getNumberOfSections(),
                                 idd.getInitialAdrOfSectionHeader());
    int is_32bit = tf->getIs32bit();

    delete tf;

    printf("FILE NAME : %s (%d bit)\n\n", x86file, is_32bit ? 32 : 64);
    idh.print();
    ids.print();
    inh.print();
    ifh.print();
    ioh.print();
    idd.print();
    printScnHeaders(ish_lst);

    return 0;
}


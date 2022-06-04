#include "header/imageDosHeader.h"
#include "header/ntHeaders/imageNtHeaders.h"
#include "header/ntHeaders/imageFileHeader.h"
#include "header/ntHeaders/opHeader/imageOptionalHeader32.h"
#include "header/ntHeaders/opHeader/imageOptionalHeader64.h"
#include "header/ntHeaders/opHeader/dataDirectory.h"
#include "header/imageSectionHeader.h"
#include "header/imageDosStub.h"

#include <list>

// /Users/choisuhyeon/Desktop/CTFLab/dreamhack 2/PEview.exe
// /Users/choisuhyeon/Desktop/CTFLab/dreamhack 2/chall9.exe

union OpHd {
    ImageOptionalHeader32 * op32;
    ImageOptionalHeader64 * op64;
};

void input(char * result, const int kLen, const char * kPrompt = "") {
    printf("%s", kPrompt);
    fgets(result, kLen, stdin);
    result[strlen(result) - 1] = '\0';
}

std::list<ImageSectionHeader> * getScnHeaders(TargetFile * file, size_t num_of_scn, size_t initial_adr) {
    auto result = new std::list<ImageSectionHeader>();

    while (num_of_scn--) {
        result->emplace_back(file, initial_adr);
        initial_adr = result->back().getNextAdrOfSectionHeader();
    }

    return result;
}

void printScnHeaders(const std::list<ImageSectionHeader> * kScnHeaders) {
    for (const ImageSectionHeader & kScnHd : *kScnHeaders) kScnHd.print();
}

int main(int argc, char ** argv) {
    using std::list;

    const unsigned kFlNmLen = 200,
                   kCmdLen  = 10;

    char file_name[kFlNmLen] = { 0 };
    if (argc ^ 1) strcpy(file_name, argv[1]);
    else          input(file_name, kFlNmLen, "file_name$ ");

    auto tf  = new TargetFile(file_name);
    auto idh = new ImageDosHeader(tf, 0);
    auto ids = new ImageDosStub(tf, idh->getInitialAdrOfNTHd());
    auto inh = new ImageNtHeaders(tf, idh->getInitialAdrOfNTHd());
    auto ifh = new ImageFileHeader(tf, inh->getInitialAdrOfFileHd());

    const bool kIs32bit = tf->getIs32bit();

    OpHd ioh {};
    if (kIs32bit) ioh.op32 = new ImageOptionalHeader32(tf, ifh->getInitialAdrOfOpHd());
    else          ioh.op64 = new ImageOptionalHeader64(tf, ifh->getInitialAdrOfOpHd());

    auto idd     = new DataDirectory(tf, kIs32bit
            ? ioh.op32->getInitialAdrOfDataDir()
            : ioh.op64->getInitialAdrOfDataDir());
    auto ish_lst = getScnHeaders(tf,
                                 ifh->getNumberOfSections(),
                                 idd->getInitialAdrOfSectionHeader());

    delete tf;

    while (true) {
        char command[kCmdLen] { 0 };
        input(command, kCmdLen, "parser$ ");

        if      (!strcmp(command, "dos-hd"))   idh->print();
        else if (!strcmp(command, "dos-stub")) ids->print();
        else if (!strcmp(command, "fl-hd"))    ifh->print();
        else if (!strcmp(command, "sc-hd"))    printScnHeaders(ish_lst);
        else if (!strcmp(command, "op-hd")) {
            if (kIs32bit) ioh.op32->print();
            else          ioh.op64->print();
            idd->print();
        }
        else if (!strcmp(command, "nt-hds")) {
            inh->print();
            ifh->print();
            if (kIs32bit) ioh.op32->print();
            else          ioh.op64->print();
            idd->print();
        }
        else if (!strcmp(command, "q")) {
            delete idh; delete ids;
            delete inh; delete ifh;
            delete idd; delete ish_lst;

            if (kIs32bit) delete ioh.op32;
            else          delete ioh.op64;

            return 0;
        }
        else printf("Undefined command: \"%s\"\n", command);
    }
}


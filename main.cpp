#include "header/imageDosHeader.h"
#include "header/ntHeaders/imageNtHeaders.h"
#include "header/ntHeaders/imageFileHeader.h"
#include "header/ntHeaders/opHeader/imageOptionalHeader32.h"
#include "header/ntHeaders/opHeader/imageOptionalHeader64.h"
#include "header/ntHeaders/opHeader/dataDirectory.h"
#include "header/imageSectionHeader.h"
#include "header/imageDosStub.h"
#include "body/imageImportDescriptor.h"
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

std::list<std::pair<size_t, size_t>> * getLstOfMainInfoOfScn(std::list<ImageSectionHeader> * scn_hds) {
    auto result = new std::list<std::pair<size_t, size_t>>();
    for (auto & kScn : *scn_hds) result->push_back(kScn.getVaPtr2raw());

    return result;
}

void printScnHeaders(const std::list<ImageSectionHeader> * kScnHeaders) {
    for (const ImageSectionHeader & kScnHd : *kScnHeaders) kScnHd.print();
}

std::list<ImageImportDescriptor> * getIIDs(
        TargetFile           * file,
        size_t                 initial_adr,
        size_t                 size,
        std::list<std::pair<size_t, size_t>> * va_ptr2raw_lst) {
    auto result = new std::list<ImageImportDescriptor>();
    auto num_of_IID = size / ImageImportDescriptor::StructSize - 1;

    initial_adr = rvaToRaw(initial_adr, va_ptr2raw_lst);

    while (num_of_IID--) {
        result->emplace_back(file, initial_adr, va_ptr2raw_lst);
        initial_adr = result->back().getNextIIDAdr();
    }

    return result;
}

void printIIDs(const std::list<ImageImportDescriptor> * kIIDs) {
    for (auto & kIID : *kIIDs) kIID.print();
}

void printHelp() {
    using std::pair;
    using std::make_pair;

    const pair<ConstCString, ConstCString> kNames[] {
            make_pair("dos-hd", "IMAGE_DOS_HEADER"),     make_pair("dos-stub", "IMAGE_DOS_STUB"),
            make_pair("nt-hds", "IMAGE_NT_HEADERS"),     make_pair("fl-hd", "IMAGE_FILE_HEADER"),
            make_pair("op-hd", "IMAGE_OPTIONAL_HEADER"), make_pair("data-dir", "IMAGE_DATA_DIRECTORY"),
            make_pair("sc-hd", "IMAGE_SECTION_HEADER"),  make_pair("imp-desc", "IMAGE_IMPORT_DESCRIPTOR")
    };

    for (size_t i = 0; i < sizeof kNames / sizeof *kNames; i++) {
        printf("%-8s : Prints the parsed result of \'%s\'%s.\n",
               kNames[i].first, kNames[i].second, i ^ 6 & i ^ 7 ? "" : "s");
    }
    puts("q        : Quits this program.");
}

int main(int argc, char ** argv) {
    using std::list;

    const unsigned kFlNmLen = 200,
                   kCmdLen  = 10;

    puts(R"(If this is your first time doing this program, put '?' in 'parser$ '.)");

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
    auto va_ptr2raw_lst = getLstOfMainInfoOfScn(ish_lst);
    auto idd_info = idd->getImportTable();
    auto idd_lst = getIIDs(tf, idd_info.first, idd_info.second, va_ptr2raw_lst);

    delete tf;

    while (true) {
        char command[kCmdLen] { 0 };
        input(command, kCmdLen, "parser$ ");

        if      (!strcmp(command, "?"))        printHelp();
        else if (!strcmp(command, "dos-hd"))   idh->print();
        else if (!strcmp(command, "dos-stub")) ids->print();
        else if (!strcmp(command, "fl-hd"))    ifh->print();
        else if (!strcmp(command, "data-dir")) idd->print();
        else if (!strcmp(command, "sc-hd"))    printScnHeaders(ish_lst);
        else if (!strcmp(command, "imp-desc")) printIIDs(idd_lst);
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


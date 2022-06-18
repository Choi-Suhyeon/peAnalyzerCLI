#include "header/imageSectionHeader.h"
#include "header/imageDosHeader.h"
#include "header/imageDosStub.h"
#include "header/ntHeaders/imageFileHeader.h"
#include "header/ntHeaders/imageNtHeaders.h"
#include "header/ntHeaders/opHeader/imageOptionalHeader32.h"
#include "header/ntHeaders/opHeader/imageOptionalHeader64.h"
#include "header/ntHeaders/opHeader/dataDirectory.h"
#include "body/imageImportDescriptor.h"

using ScnHdList = std::list<ImageSectionHeader>;
using IIDList   = std::list<ImageImportDescriptor>;

union OpHd {
    ImageOptionalHeader32 * op32;
    ImageOptionalHeader64 * op64;
};

void            input(char *, int, const char * kPrompt = "");
ScnHdList *     getScnHeaders(TargetFile *, size_t, size_t);
SizeTPairList * getLstOfMainInfoOfScn(const ScnHdList *);
void            printScnHeaders(const ScnHdList *);
IIDList *       getIIDs(TargetFile *, size_t, size_t, SizeTPairList *);
void            printIIDs(const IIDList *);
void            printHelp();

int main(int argc, char ** argv) {
    using std::list;

    const unsigned kFlNmLen = 200,
                   kCmdLen  = 10;

    puts(R"(If this is your first time doing this program, put '?' in 'parser$ '.)");

    char file_name[kFlNmLen] = { 0 };
    if (argc ^ 1) strcpy(file_name, argv[1]);
    else          input(file_name, kFlNmLen, "file_name$ ");

    const auto kpFile      = new TargetFile(file_name);
    const auto kpDosHeader = new ImageDosHeader(kpFile, 0);
    const auto kpDosStub   = new ImageDosStub(kpFile, kpDosHeader->getInitialAdrOfNTHd());
    const auto kpNtHeaders = new ImageNtHeaders(kpFile, kpDosHeader->getInitialAdrOfNTHd());
    const auto kpFlHeader  = new ImageFileHeader(kpFile, kpNtHeaders->getInitialAdrOfFileHd());

    const bool kIs32bit    = kpFile->getIs32bit();

    OpHd op_header {};
    if (kIs32bit) op_header.op32 = new ImageOptionalHeader32(kpFile, kpFlHeader->getInitialAdrOfOpHd());
    else          op_header.op64 = new ImageOptionalHeader64(kpFile, kpFlHeader->getInitialAdrOfOpHd());

    const auto kpDataDirectory = new DataDirectory(kpFile, kIs32bit
            ? op_header.op32->getInitialAdrOfDataDir()
            : op_header.op64->getInitialAdrOfDataDir());
    const auto kScnHeaders     = getScnHeaders(kpFile,
                                              kpDataDirectory->getInitialAdrOfSectionHeader(),
                                              kpFlHeader->getNumberOfSections());
    const auto kVaPtr2rawLst   = getLstOfMainInfoOfScn(kScnHeaders);
    const auto kIIDInfo        = kpDataDirectory->getImportTable();
    const auto kIIDs           = getIIDs(kpFile, kIIDInfo.first, kIIDInfo.second, kVaPtr2rawLst);

    delete kpFile;

    while (true) {
        char command[kCmdLen] { 0 };
        input(command, kCmdLen, "parser$ ");

        if      (!strcmp(command, "?"))        printHelp();
        else if (!strcmp(command, "dos-hd"))   kpDosHeader->print();
        else if (!strcmp(command, "dos-stub")) kpDosStub->print();
        else if (!strcmp(command, "fl-hd"))    kpFlHeader->print();
        else if (!strcmp(command, "data-dir")) kpDataDirectory->print();
        else if (!strcmp(command, "sc-hd"))    printScnHeaders(kScnHeaders);
        else if (!strcmp(command, "imp-desc")) printIIDs(kIIDs);
        else if (!strcmp(command, "op-hd")) {
            if (kIs32bit) op_header.op32->print();
            else          op_header.op64->print();
            kpDataDirectory->print();
        }
        else if (!strcmp(command, "nt-hds")) {
            kpNtHeaders->print();
            kpFlHeader->print();
            if (kIs32bit) op_header.op32->print();
            else          op_header.op64->print();
            kpDataDirectory->print();
        }
        else if (!strcmp(command, "q")) {
            delete kpDosHeader;     delete kpDosStub;
            delete kpNtHeaders;     delete kpFlHeader;
            delete kpDataDirectory; delete kScnHeaders;
            delete kVaPtr2rawLst;   delete kIIDs;

            if (kIs32bit) delete op_header.op32;
            else          delete op_header.op64;

            return 0;
        }
        else printf("Undefined command: \"%s\"\n", command);
    }
}

void input(char * result, const int kLen, const char * kPrompt) {
    printf("%s", kPrompt);
    fgets(result, kLen, stdin);
    result[strlen(result) - 1] = '\0';
}

ScnHdList * getScnHeaders(TargetFile * file, size_t initial_adr, size_t num_of_scn) {
    auto result = new ScnHdList();

    while (num_of_scn--) {
        result->emplace_back(file, initial_adr);
        initial_adr = result->back().getNextAdrOfSectionHeader();
    }

    return result;
}

SizeTPairList * getLstOfMainInfoOfScn(const ScnHdList * kScnHds) {
    auto result = new SizeTPairList();
    for (auto & kScn : *kScnHds) result->push_back(kScn.getVaPtr2raw());

    return result;
}

void printScnHeaders(const ScnHdList * kScnHds) {
    for (const auto & kScnHd : *kScnHds) kScnHd.print();
}

IIDList * getIIDs(
        TargetFile    * file,
        size_t          initial_adr,
        size_t          size,
        SizeTPairList * va_ptr2raw_lst) {
    auto result = new IIDList();
    auto num_of_IID = size / ImageImportDescriptor::StructSize_ - 1;

    initial_adr = rvaToRaw(initial_adr, va_ptr2raw_lst);

    while (num_of_IID--) {
        result->emplace_back(file, initial_adr, va_ptr2raw_lst);
        initial_adr = result->back().getNextIIDAdr();
    }

    return result;
}

void printIIDs(const IIDList * kIIDs) {
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

// /Users/choisuhyeon/Desktop/CTFLab/dreamhack 2/PEview.exe
// /Users/choisuhyeon/Desktop/CTFLab/dreamhack 2/chall9.exe
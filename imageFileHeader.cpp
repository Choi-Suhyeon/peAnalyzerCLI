#include "imageFileHeader.h"

ImageFileHeader::ImageFileHeader(TargetFile & file, const unsigned initial_adr)
: AbstractPEStruct(file, initial_adr, 7, 0x14) {
    using std::byte;

    const unsigned kSize      = getSize();
    const unsigned kNumOfElem = getNumOfElem();

    sub_bin_ = new byte[kSize];
    getFile().getFileContents(sub_bin_, getInitialAdr(), kSize);

    auto current_adr = new unsigned(0);
    for (unsigned i = kNumOfElem; i; i--) {
        const unsigned kIdx  = kNumOfElem - i;
        const unsigned kData = TargetFile::getSubBytes(sub_bin_, *current_adr, kSizeArr[kIdx]);

        char * value = nullptr;

        switch(kIdx) {
            case 0: {
                switch(kData) {
                    case 0x0000: value = (char *)"IMAGE_FILE_MACHINE_UNKNOWN";   break;
                    case 0x014C: value = (char *)"IMAGE_FILE_MACHINE_I386";      break;
                    case 0x0162: value = (char *)"IMAGE_FILE_MACHINE_R3000";     break;
                    case 0x0166: value = (char *)"IMAGE_FILE_MACHINE_R4000";     break;
                    case 0x0168: value = (char *)"IMAGE_FILE_MACHINE_R10000";    break;
                    case 0x0169: value = (char *)"IMAGE_FILE_MACHINE_WCEMIPSV2"; break;
                    case 0x0184: value = (char *)"IMAGE_FILE_MACHINE_ALPHA";     break;
                    case 0x01A2: value = (char *)"IMAGE_FILE_MACHINE_SH3";       break;
                    case 0x01A3: value = (char *)"IMAGE_FILE_MACHINE_SH3DSP";    break;
                    case 0x01A4: value = (char *)"IMAGE_FILE_MACHINE_SH3E";      break;
                    case 0x01A6: value = (char *)"IMAGE_FILE_MACHINE_SH4";       break;
                    case 0x01A8: value = (char *)"IMAGE_FILE_MACHINE_SH5";       break;
                    case 0x01C0: value = (char *)"IMAGE_FILE_MACHINE_ARM";       break;
                    case 0x01C2: value = (char *)"IMAGE_FILE_MACHINE_THUMB";     break;
                    case 0x01C4: value = (char *)"IMAGE_FILE_MACHINE_ARMNT";     break;
                    case 0x01D3: value = (char *)"IMAGE_FILE_MACHINE_AM33";      break;
                    case 0x01F0: value = (char *)"IMAGE_FILE_MACHINE_POWERPC";   break;
                    case 0x01F1: value = (char *)"IMAGE_FILE_MACHINE_POWERPCFP"; break;
                    case 0x0200: value = (char *)"IMAGE_FILE_MACHINE_IA64";      break;
                    case 0x0266: value = (char *)"IMAGE_FILE_MACHINE_MIPS16";    break;
                    case 0x0284: value = (char *)"IMAGE_FILE_MACHINE_ALPHA64";   break;
                    case 0x0366: value = (char *)"IMAGE_FILE_MACHINE_MIPSFPU";   break;
                    case 0x0466: value = (char *)"IMAGE_FILE_MACHINE_MIPSFPU16"; break;                     break;
                    case 0x0520: value = (char *)"IMAGE_FILE_MACHINE_TRICORE";   break;
                    case 0x0CEF: value = (char *)"IMAGE_FILE_MACHINE_CEF";       break;
                    case 0x0EBC: value = (char *)"IMAGE_FILE_MACHINE_EBC";       break;
                    case 0x8664: value = (char *)"IMAGE_FILE_MACHINE_AMD64";     break;
                    case 0x9041: value = (char *)"IMAGE_FILE_MACHINE_M32R";      break;
                    case 0xC0EE: value = (char *)"IMAGE_FILE_MACHINE_CEE";       break;
                    default: break;
                } break;
            }
            case 2: {
                value = asctime(gmtime((time_t *) &kData));
                break;
            }
            case 6: {
                for (unsigned j = kNumOfChar, filter = 0xF; j; j--, filter <<= 4) {
                    const unsigned kJdx = kNumOfChar - j;

                    switch((kData & filter) >> kNumOfChar * kJdx) {
                        case 8:  if (kJdx != 1) { charIndices[kJdx] = 3; break; }
                        case 4:  charIndices[kJdx] = 2;  break;
                        case 2:  charIndices[kJdx] = 1;  break;
                        case 1:  charIndices[kJdx] = 0;  break;
                        default: charIndices[kJdx] = -1; break;
                    }
                }
            }
            default: break;
        }

        elem_info_[kIdx].name = kNameArr[kIdx];
        elem_info_[kIdx].desc = kDescArr[kIdx];
        elem_info_[kIdx].size = kSizeArr[kIdx];
        elem_info_[kIdx].adr  = *current_adr;
        elem_info_[kIdx].val  = value ? value : "";

        *current_adr += kSizeArr[kIdx];
    }
    delete current_adr;
}

ImageFileHeader::~ImageFileHeader() {
    delete [] kNameArr;
    delete [] kDescArr;
    delete [] kSizeArr;
    delete [] kDescOfCharArr;
    delete [] charIndices;
}

void ImageFileHeader::print() {
    AbstractPEStruct::print();

    for (unsigned i = kNumOfChar; i; i--) {
        const unsigned kIdx = kNumOfChar - i;
        if (charIndices[kIdx] == -1) continue;
        printf("%s\n", kDescOfCharArr[kIdx][charIndices[kIdx]]);
    }
    printf("\n");
}

unsigned ImageFileHeader::getInitialAdrOfOpHd() {
    return getInitialAdr() + getSize();
}

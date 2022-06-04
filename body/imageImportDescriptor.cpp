#include "imageImportDescriptor.h"

ImageImportDescriptor::ImageImportDescriptor(TargetFile * const kFile, const size_t kInitialAdr)
: AbstractPEStruct(kFile, kInitialAdr, 5, 0x14) {

}

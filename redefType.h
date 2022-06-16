#ifndef PEANALCLI_REDEFTYPE_H
#define PEANALCLI_REDEFTYPE_H

#include <list>
#include "header/imageSectionHeader.h"
#include "body/imageImportDescriptor.h"
using ConstCString    = const char *;
using ConstCStringArr = ConstCString const * const;
using ConstSizeT      = const size_t;
using ConstSizeTArr   = ConstSizeT * const;
using ScnHdList       = std::list<ImageSectionHeader>;
using IIDList         = std::list<ImageImportDescriptor>;
using SizeTPair       = std::pair<size_t, size_t>;

#endif //PEANALCLI_REDEFTYPE_H

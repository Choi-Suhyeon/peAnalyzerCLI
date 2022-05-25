#ifndef PEANALCLI_ABSTRACTPESTRUCT_H
#define PEANALCLI_ABSTRACTPESTRUCT_H

#include "targetFile.h"
#include "abstractPEStruct.h"

using ConstCString    = const char *;
using ConstCStringArr = ConstCString const * const;
using ConstSizeT      = const size_t;
using ConstSizeTArr   = ConstSizeT * const;

class AbstractPEStruct {
    TargetFile * file_ = nullptr;
    size_t   initial_adr_ = 0; // 파일 내에서 절대 주소
    size_t   num_of_elem_ = 0;
    size_t   size_        = 0;

    struct ElementDetails_ {
        const char * name;
        const char * val;
        size_t       size;
        size_t       adr; // initial adr 기준 상대 주소
    };

protected:
    static const size_t kSzOfBYTE_,
                        kSzOfWORD_,
                        kSzOfDWORD_,
                        kSzOfQWORD_;

    ElementDetails_ * elem_info_  = nullptr;
    std::byte       * sub_bin_    = nullptr;

    explicit AbstractPEStruct(TargetFile *, size_t, size_t, size_t);
    virtual ~AbstractPEStruct();

    virtual void print();

    [[nodiscard]] size_t       getInitialAdr() const;
    [[nodiscard]] size_t       getSize()       const;
    [[nodiscard]] size_t       getNumOfElem()  const;
    [[nodiscard]] bool         getIs32bit();
    [[nodiscard]] TargetFile * getFile();
};

#endif //PEANALCLI_ABSTRACTPESTRUCT_H

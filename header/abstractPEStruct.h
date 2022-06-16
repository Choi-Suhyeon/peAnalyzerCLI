#ifndef PEANALCLI_ABSTRACTPESTRUCT_H
#define PEANALCLI_ABSTRACTPESTRUCT_H

#include "../file_byte/targetFile.h"
#include "../redefType.h"
#include <cstring>

class AbstractPEStruct {
    TargetFile * file_        = nullptr;
    size_t       initial_adr_ = 0,
                 num_of_elem_ = 0,
                 size_        = 0;
    bool         is_32bit_    = false;

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

protected:
    virtual ~AbstractPEStruct();

    virtual void print() const;

    [[nodiscard]] size_t       getInitialAdr() const;
    [[nodiscard]] size_t       getSize()       const;
    [[nodiscard]] size_t       getNumOfElem()  const;
    [[nodiscard]] bool         getIs32bit()    const;
    [[nodiscard]] TargetFile * getFile();
};

#endif //PEANALCLI_ABSTRACTPESTRUCT_H

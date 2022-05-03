#ifndef PEANALCLI_ABSTRACTPESTRUCT_H
#define PEANALCLI_ABSTRACTPESTRUCT_H

#include "targetFile.h"
#include "abstractPEStruct.h"
#include <iostream>

class AbstractPEStruct {
    TargetFile file_;
    unsigned   initial_adr_ = 0; // 파일 내에서 절대 주소
    unsigned   num_of_elem_ = 0;
    unsigned   size_        = 0;

    union Address_ {
        std::byte bit32[4];
        std::byte bit64[8];
    };

    struct ElementDetails_ {
        const char * name;
        const char * desc;
        const char * val;
        unsigned     size;
        Address_     adr; // initial adr 기준 상대 주소
    };

protected:
    static const unsigned kSzOfBYTE_;
    static const unsigned kSzOfWORD_;
    static const unsigned kSzOfDWORD_;
    static const unsigned kSzOfQWORD_;
    static const unsigned kSzOfAdr32_;
    static const unsigned kSzOfAdr64_;

    ElementDetails_ * elem_info_  = nullptr;
    std::byte       * sub_bin_    = nullptr;

    explicit AbstractPEStruct(TargetFile &, unsigned, unsigned, unsigned);
    ~AbstractPEStruct();

    virtual void print();

    [[nodiscard]] unsigned     getInitialAdr() const;
    [[nodiscard]] unsigned     getSize()       const;
    [[nodiscard]] unsigned     getNumOfElem()  const;
    [[nodiscard]] bool         getIs32bit();
    [[nodiscard]] TargetFile & getFile();
};

#endif //PEANALCLI_ABSTRACTPESTRUCT_H

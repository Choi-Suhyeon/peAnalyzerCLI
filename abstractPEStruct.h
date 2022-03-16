#ifndef PEANALCLI_ABSTRACTPESTRUCT_H
#define PEANALCLI_ABSTRACTPESTRUCT_H

#import "targetFile.h"
#import <iostream>

class AbstractPEStruct {
    static const unsigned kSzOfBYTE  = 1;
    static const unsigned kSzOfWORD  = 2;
    static const unsigned kSzOfDWORD = 4;
    static const unsigned kSzOfQWORD = 8;
    static const unsigned kSzOfAdr32 = 4;
    static const unsigned kSzOfAdr64 = 8;

    TargetFile file_;
    unsigned   initial_adr_ = 0; // 파일 내에서 절대 주소
    unsigned   num_of_elem_ = 0;
    unsigned   size_        = 0;

    union Address_ {
        std::byte bit32[kSzOfAdr32];
        std::byte bit64[kSzOfAdr64];
    };

    struct ElementDetails_ {
        const char * name;
        const char * desc;
        const char * val;
        unsigned     size;
        Address_     adr; // initial adr 기준 상대 주소
    };

protected:
    ElementDetails_ * elem_info_  = nullptr;

    explicit AbstractPEStruct(TargetFile &, unsigned, unsigned, unsigned);
    ~AbstractPEStruct();

    virtual void print();

    [[nodiscard]] static unsigned    getSzOfBYTE();
    [[nodiscard]] static unsigned    getSzOfWORD();
    [[nodiscard]] static unsigned    getSzOfDWORD();
    [[nodiscard]] static unsigned    getSzOfQWORD();
    [[nodiscard]] static unsigned    getSzOfAdr32();
    [[nodiscard]] static unsigned    getSzOfAdr64();
    [[nodiscard]]        unsigned    getInitialAdr() const;
    [[nodiscard]]        unsigned    getSize()       const;
    [[nodiscard]]        unsigned    getNumOfElem()  const;
    [[nodiscard]]        bool        getIs32bit();
    [[nodiscard]]       TargetFile & getFile();
};

#endif //PEANALCLI_ABSTRACTPESTRUCT_H

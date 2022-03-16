#ifndef PEANALCLI_TARGETFILE_H
#define PEANALCLI_TARGETFILE_H

#import "byte.h"
#import <fstream>

class TargetFile {
    std::ifstream tgt_file_;

public:
    explicit TargetFile(const std::string &);
    TargetFile(TargetFile &);
    ~TargetFile();

    void     getFileContents(std::byte [], unsigned, unsigned);
    unsigned getFileContents(unsigned, unsigned);
    bool     check32bit();
};

#endif //PEANALCLI_TARGETFILE_H

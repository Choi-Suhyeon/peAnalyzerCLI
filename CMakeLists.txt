cmake_minimum_required(VERSION 3.21)
project(peAnalCLI)

set(CMAKE_CXX_STANDARD 20)

add_executable(peAnalCLI main.cpp byte.cpp byte.h targetFile.cpp targetFile.h abstractPEStruct.cpp abstractPEStruct.h imageDosHeader.cpp imageDosHeader.h imageDosStub.cpp imageDosStub.h imageNtHeaders.cpp imageNtHeaders.h imageFileHeader.cpp imageFileHeader.h imageOptionalHeader32.cpp imageOptionalHeader32.h)

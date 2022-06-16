cmake_minimum_required(VERSION 3.21)
project(peAnalCLI)

set(CMAKE_CXX_STANDARD 20)

add_executable(peAnalCLI main.cpp file_byte/byte.cpp file_byte/byte.h file_byte/targetFile.cpp file_byte/targetFile.h header/abstractPEStruct.cpp header/abstractPEStruct.h header/imageDosHeader.cpp header/imageDosHeader.h header/imageDosStub.cpp header/imageDosStub.h header/ntHeaders/imageNtHeaders.cpp header/ntHeaders/imageNtHeaders.h header/ntHeaders/imageFileHeader.cpp header/ntHeaders/imageFileHeader.h header/ntHeaders/opHeader/imageOptionalHeader32.cpp header/ntHeaders/opHeader/imageOptionalHeader32.h header/ntHeaders/opHeader/imageOptionalHeader64.cpp header/ntHeaders/opHeader/imageOptionalHeader64.h header/ntHeaders/opHeader/optionalHeaderInterface.cpp header/ntHeaders/opHeader/optionalHeaderInterface.h header/ntHeaders/opHeader/dataDirectory.cpp header/ntHeaders/opHeader/dataDirectory.h header/imageSectionHeader.cpp header/imageSectionHeader.h body/imageImportDescriptor.cpp body/imageImportDescriptor.h redefType.h)

# IF THIS SHELL IS NOT WORKING
# TRY THIS >> chmod 755 clean.sh
#!/bin/bash
echo "CMAKE DUMMY 빌드 파일들을 지웁니다."

DIR="$( cd "$( dirname "$0" )" && pwd -P )"
cd $DIR
sudo rm -rf CMakeCache.txt
sudo rm -rf Makefile
sudo rm -rf cmake_install.cmake
sudo rm -rf CMakeFiles/*
y
sudo rmdir $(pwd)/CMakeFiles
wait
echo "빌드 파일을 지웠습니다."

cmake CMakeLists.txt
wait
make

sudo rm -rf CMakeCache.txt
sudo rm -rf Makefile
sudo rm -rf cmake_install.cmake
sudo rm -rf CMakeFiles/*
sudo rmdir $(pwd)/CMakeFiles
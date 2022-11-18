#!/bin/sh
set -eux
PWD=$(pwd)

git submodule init
git submodule update --recursive --init

echo "---------------------Building the chops library!--------------------"
mkdir -p build
cd build
mkdir -p install
cmake .. 
cmake --build .
cmake --install . --config Debug --prefix "${PWD}/install"

echo "---------Building the ctest library (unit test dependency)!---------"
cd install
cmake -S../../tests/deps/ctest -B./ctest -Duse_coloring:bool=ON
cmake --build ./ctest
cmake --install ./ctest --config Debug --prefix "${PWD}/ctest"
cp ${PWD}/ctest/libctest.a ${PWD}/lib
cp ${PWD}/ctest/deps/c-logging/libc_logging.a ${PWD}/lib

#build the tests
echo "---------------------Building the chops tests!---------------------"
export LD_LIBRARY_PATH=${PWD}/lib:$LD_LIBRARY_PATH
cmake ../../tests -Dchops_DIR="${PWD}/lib/cmake/chops"
cmake --build .

cd ../..
echo "--------------Running valgrind to check memory errors!-------------"
valgrind --leak-check=full --track-origins=yes -s build/install/chops-tests
echo "------------------------Running unittests!-------------------------"
./build/install/chops-tests

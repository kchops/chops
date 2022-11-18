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
cmake ../../tests -Dchops_DIR="${PWD}/lib/cmake/chops"
cmake --build .

cd ../..
echo "------------------------Running unittests!-------------------------"
./build/install/chops-tests

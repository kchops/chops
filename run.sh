#!/bin/sh
set -euxo pipefail

echo "---------------------Building the chops library!--------------------"
mkdir -p build
cd build
mkdir -p install
cmake .. 
cmake --build .
cmake --install . --config Debug --prefix "/home/runner/chops/build/install"

echo "---------Building the ctest library (unit test dependency)!---------"
cd install
cmake -S../../tests/deps/ctest -B./ctest -Duse_coloring:bool=ON
cmake --build ./ctest
cmake --install ./ctest --config Debug --prefix "/home/runner/chops/build/install/ctest"
cp /home/runner/chops/build/install/ctest/libctest.a /home/runner/chops/build/install/lib
cp /home/runner/chops/build/install/ctest/deps/c-logging/libc_logging.a /home/runner/chops/build/install/lib

#build the tests
echo "---------------------Building the chops tests!---------------------"
export LD_LIBRARY_PATH=/home/runner/chops/install/lib:$LD_LIBRARY_PATH
cmake ../../tests -Dchops_DIR="/home/runner/chops/build/install/lib/cmake/chops"
cmake --build .

cd ../..
echo "--------------Running valgrind to check memory errors!-------------"
valgrind --leak-check=full --track-origins=yes -s build/install/chops-tests
echo "------------------------Running unittests!-------------------------"
./build/install/chops-tests
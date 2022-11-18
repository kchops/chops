# test for now at least that we are compiling on windows

git submodule init
git submodule update --recursive --init

cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -S"$pwd" -B"$pwd/build" -G "Visual Studio 17 2022" -T host=x64 -A x64
cmake --build "$pwd/build" --config Debug --target ALL_BUILD -j 14 --

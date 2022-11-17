cmake_minimum_required(VERSION 3.18)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET_NAME chops-tests)
project(${TARGET_NAME})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-incompatible-pointer-types")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-pointer-arith")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wpedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g")

add_executable(${TARGET_NAME} main.c)
find_package(chops REQUIRED)
target_link_libraries(${TARGET_NAME} chops::chops)
set_target_properties(
    chops::chops
    PROPERTIES IMPORTED_LOCATION
    /home/runner/chops/install/lib/libchops.so
)

include(../cmake/debug-helpers.cmake)
print_target_properties(chops::chops)
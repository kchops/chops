cmake_minimum_required(VERSION 3.18)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(TARGET_NAME chops-tests)
project(${TARGET_NAME})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-incompatible-pointer-types")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-pointer-arith")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-function")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g")

file(GLOB C_SOURCE_FILES ./*.c)
add_executable(${TARGET_NAME} ${C_SOURCE_FILES})
find_package(chops REQUIRED)

target_include_directories(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/deps/ctest/inc
    ${CMAKE_CURRENT_LIST_DIR}/deps/ctest/deps/macro-utils-c/inc
    ${CMAKE_CURRENT_LIST_DIR}/deps/ctest/deps/c-logging/inc
)

target_link_libraries(${TARGET_NAME} ${chops-tests_BINARY_DIR}/lib/libctest.a)
target_link_libraries(${TARGET_NAME} ${chops-tests_BINARY_DIR}/lib/libc_logging.a)
target_link_libraries(${TARGET_NAME} chops::chops)

set_target_properties(
    chops::chops
    PROPERTIES IMPORTED_LOCATION
    /home/runner/chops/build/install/lib/libchops.so
)

# include(../cmake/debug-helpers.cmake)
# dump_cmake_variables()
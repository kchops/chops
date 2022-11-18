cmake_minimum_required(VERSION 3.18)

project(chops)
set(TARGET_NAME chops)
set(CHOPS_VERSION 0.0.1)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB C_SOURCE_FILES ./src/*.c)
file(GLOB C_HEADER_FILES ./inc/*.h)

if(MSVC)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
    add_compile_options(/wd4133)
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-incompatible-pointer-types")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-pointer-arith")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wpedantic")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g")
endif()

add_library(${TARGET_NAME} SHARED ${C_SOURCE_FILES})
set_property(TARGET ${TARGET_NAME} PROPERTY C_STANDARD 99)
target_include_directories(${TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)

install(TARGETS ${TARGET_NAME} 
    EXPORT ${TARGET_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)

install(EXPORT ${TARGET_NAME}Targets
    FILE ${TARGET_NAME}Targets.cmake
    NAMESPACE ${TARGET_NAME}::
    DESTINATION lib/cmake/${TARGET_NAME})

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${TARGET_NAME}ConfigVersion.cmake"
    VERSION ${CHOPS_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(FILES "${TARGET_NAME}Config.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}ConfigVersion.cmake"
    DESTINATION lib/cmake/${TARGET_NAME})

install(FILES ${C_HEADER_FILES} DESTINATION include)
cmake_minimum_required(VERSION 3.22)

SET(PROJECT_NAME CASTANETS_SERIALCOMM)

project(${PROJECT_NAME} VERSION 0.0.1 DESCRIPTION "mylib description")

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install")

option(BUILD_TESTS "Build tests" ON)

add_library(${PROJECT_NAME} 
    SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib.cpp
)

add_subdirectory(extern)
add_subdirectory(src)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    OUTPUT_NAME ${PROJECT_NAME}
    PUBLIC_HEADER
        "include/lib.h;include/shared/dataStruct.h"
    BUILD_RPATH "\$ORIGIN"
    INSTALL_RPATH "\$ORIGIN"
)

set(CMAKE_CXX_VISIBILITY_PRESET default)
set(CMAKE_VISIBILITY_INLINES_HIDDEN OFF)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS ON
    )
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/extern/nano-signal-slot/nano-signal-slot-src
        ${CMAKE_CURRENT_SOURCE_DIR}/extern/spdlog/include
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
    nano_signal_slot
    spdlog::spdlog_header_only
)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX
        "${CMAKE_BINARY_DIR}/install"
        CACHE PATH "Install path" FORCE
    )
endif()

## C# / Unity
install(TARGETS ${PROJECT_NAME} 
    DESTINATION 
        ${CMAKE_CURRENT_SOURCE_DIR}/../csharp-unity/Plugins/${CMAKE_SYSTEM_NAME}
)

## Unreal Engine
# Main library
install(TARGETS ${PROJECT_NAME} 
    DESTINATION 
    ${CMAKE_CURRENT_SOURCE_DIR}/../unreal/Extras/libcastanets/${CMAKE_SYSTEM_NAME}/
PUBLIC_HEADER 
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/../unreal/Source/LibNFCCrossEngine/Public
)
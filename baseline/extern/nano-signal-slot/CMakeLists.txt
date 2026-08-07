## Meha555
cmake_minimum_required(VERSION 3.14)
project(nano-signal-slot VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(NANO_BUILD_TESTS "Build unit tests" ON)
option(NANO_BUILD_EXAMPLES "Build examples" OFF)

add_library(nano_signal_slot INTERFACE)
add_library(nano-signal-slot::nano_signal_slot ALIAS nano_signal_slot)

target_include_directories(nano_signal_slot INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

if(NANO_BUILD_TESTS)
    find_package(GTest REQUIRED)
    enable_testing()
    add_subdirectory(tests)
endif()

install(TARGETS nano_signal_slot
    EXPORT nano-signal-slot-targets
    INCLUDES DESTINATION include
)

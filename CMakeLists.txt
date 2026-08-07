cmake_minimum_required( VERSION 3.22 )
project(CASTANETS_SERIALCOMM-metaproject)
set(CMAKE_BUILD_TYPE Debug)
message( STATUS "Using CMake ${CMAKE_VERSION}" )
option(BUILD_GODOT "Build Godot module" ON)
option(BUILD_DOTNET "Build DOTNET module" OFF) #WIP

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)
add_subdirectory(baseline)
if(BUILD_GODOT)
    message("GODOT BUILD ON")
    add_subdirectory(godot)
endif()

if(BUILD_DOTNET)
        message("DOTNET BUILD ON")
        add_subdirectory(csharp-unity)
endif()
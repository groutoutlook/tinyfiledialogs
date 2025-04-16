cmake_minimum_required(VERSION 4.0)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build using shared libraries" FORCE)

set(TFD_BUILD_EXAMPLES OFF CACHE BOOL "Build the example executable")

project(tinyfiledialogs)
enable_language(C)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 23)

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
endif()

if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
endif()

add_library(tinyfiledialogs)

# WARN: No glob, since it somehow grabs CmakeCXXCompiler.cpp files which have a placeholder main() symbol there.
file(GLOB_RECURSE TFD_SRC "./tinyfiledialogs.c" "./tinyfiledialogs.h" "./tinyfd_moredialogs.c" "./tinyfd_moredialogs.h" "./tfd.hpp")
target_sources(tinyfiledialogs PUBLIC ${TFD_SRC})

target_include_directories(tinyfiledialogs PUBLIC ".")
target_compile_features(tinyfiledialogs PUBLIC cxx_std_23)

if (TFD_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
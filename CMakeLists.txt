cmake_minimum_required(VERSION 4.0)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build using shared libraries" FORCE)

set(TFD_BUILD_EXAMPLES OFF CACHE BOOL "Build the example executable")
#option(TFD_BUILD_EXAMPLES "Build the example executable" OFF)
# option(TFD_INSTALL        "Enable the install command"   ON)

project(tinyfiledialogs)
enable_language(C)

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
file(GLOB_RECURSE TFD_SRC "./tinyfiledialogs.c" "./tinyfiledialogs.h" "./tinyfd_moredialogs.c" "./tinyfd_moredialogs.h")
target_sources(tinyfiledialogs PUBLIC ${TFD_SRC})

target_include_directories(tinyfiledialogs PUBLIC ".")

if (TFD_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
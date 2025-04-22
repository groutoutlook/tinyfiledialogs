cmake_minimum_required(VERSION 4.0)

set(TFD_BUILD_EXAMPLES OFF CACHE BOOL "Build the example executable")

project(tinyfiledialogs)
enable_language(C)

if (PROJECT_IS_TOP_LEVEL)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin-lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin-etc")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
endif()


# Main C++ sources
set(TFD_SOURCES
    "./tinyfiledialogs.c" 
    "./tinyfd_moredialogs.c"
)

set(TFD_HEADERS
    "./tinyfiledialogs.h" 
    "./tinyfd_moredialogs.h"
    "./tfd.hpp"
)

# Create the C++ library
add_library(tinyfiledialogs STATIC ${TFD_SOURCES} ${TFD_HEADERS})

target_include_directories(tinyfiledialogs PUBLIC ".")
target_compile_features(tinyfiledialogs PUBLIC cxx_std_23)

if (TFD_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
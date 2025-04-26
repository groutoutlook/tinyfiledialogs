cmake_minimum_required(VERSION 4.0)

project(tfd_examples)

enable_language(C)
enable_language(CXX)

add_executable(hello hello.c)
target_link_libraries(hello PRIVATE tinyfiledialogs)
set_target_properties(hello PROPERTIES C_STANDARD 11)

add_executable(hello_tfd hello_tfd.cpp)
target_link_libraries(hello_tfd PRIVATE tinyfiledialogs)
set_target_properties(hello_tfd PROPERTIES CXX_STANDARD 23)

add_executable(hello_wchar hello_wchar_t.c)
target_link_libraries(hello_wchar PRIVATE tinyfiledialogs)
set_target_properties(hello_wchar PROPERTIES C_STANDARD 11)
cmake_minimum_required(VERSION 4.0)

add_executable(hello hello.c)
target_link_libraries(hello PRIVATE tinyfiledialogs)

add_executable(hello_tfd hello_tfd.cpp)
target_link_libraries(hello_tfd PRIVATE tinyfiledialogs)

add_executable(hello_wchar hello_wchar_t.c)
target_link_libraries(hello_wchar PRIVATE tinyfiledialogs)
cmake_minimum_required(VERSION 4.0)

add_executable(hello hello.c)
target_link_libraries(hello PRIVATE tinyfiledialogs)

add_executable(moredialogs tinyfd_moredialogs.c)
target_link_libraries(moredialogs PRIVATE tinyfiledialogs)
cmake_minimum_required(VERSION 3.19)
project(gdbus C)

set(CMAKE_C_STANDARD 99)

include_directories(
        gdbus
        /usr/include/glib-2.0
        /usr/lib/x86_64-linux-gnu/glib-2.0/include
        /usr/include/gio-unix-2.0
)

aux_source_directory(gdbus/generate generate)
aux_source_directory(gdbus interface)

add_executable(gdbus ${generate} ${interface} main.c)

target_link_libraries(gdbus glib-2.0 gio-2.0 gobject-2.0)
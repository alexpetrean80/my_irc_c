cmake_minimum_required(VERSION 3.25)
project(client C)

set(CMAKE_C_STANDARD 11)

include_directories(../lib)
include_directories(../lib/user_info)
include_directories(.)
include_directories(server)
include_directories(server/server_list)
include_directories(ui/menu)
include_directories(ui/utils)

add_executable(client
        ../lib/user_info/user_info.c
        ../lib/user_info/user_info.h
        ../lib/globals.h
        server/server_list/server_list.c
        server/server_list/server_list.h
        server/server.c
        server/server.h
        ui/menu/menu.c
        ui/menu/menu.h
        ui/utils/utils.c
        ui/utils/utils.h
        main.c
        options.h)

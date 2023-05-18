cmake_minimum_required(VERSION 3.25)
project(server C)

set(CMAKE_C_STANDARD 11)

include_directories(../lib)
include_directories(../lib/user_info)
include_directories(channel)
include_directories(message)

add_executable(server
        ../lib/user_info/user_info.c
        ../lib/user_info/user_info.h
        ../lib/globals.h
        channel/channel.c
        channel/channel.h
        message/message.c
        message/message.h
        main.c)

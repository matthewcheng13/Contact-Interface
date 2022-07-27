cmake_minimum_required(VERSION 3.17)
project(Assignment_6 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Assignment_6
        contact.c
        contact.h
        contact_list.c
        contact_list.h
        main.c
        utils.c
        utils.h
        addr.csv)

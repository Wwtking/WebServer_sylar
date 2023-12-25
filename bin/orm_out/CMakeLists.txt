cmake_minimum_required(VERSION 3.0)
project(orm_data)

set(LIB_SRC
    test/orm/user_info.cpp
)

add_library(orm_data ${LIB_SRC})
redefine_file_macro(orm_data)

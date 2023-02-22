# When a figure out how this work a will used its

cmake_minimum_required(VERSION 3.16.3)
project(Dariu)
set(CMAKE_CXX_STANDARD 11)
# include_directories("../src/model/")
add_executable(Dariu ../src/main.cpp)

add_executable(MyExec
  src/main.c
  src/other_source.c
  include/header1.h
  include/header2.h
)

target_link_libraries(Dariu sfml-graphics)
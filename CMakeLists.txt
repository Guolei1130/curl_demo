cmake_minimum_required(VERSION 3.12)
project(untitled)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_DL_LIBS -lcurl)

add_executable(untitled HttpClient.h HttpCallback.h HttpClient.cpp  main.cpp )

target_link_libraries(untitled curl)
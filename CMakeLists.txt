cmake_minimum_required(VERSION 3.31)
project(webserverCPP)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(server)

add_subdirectory(toml11)

add_executable(nduboiServer main.cpp)

target_link_libraries(server PRIVATE toml11::toml11)

target_link_libraries(nduboiServer PRIVATE server)

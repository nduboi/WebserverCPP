cmake_minimum_required(VERSION 3.31)
project(webserverCPP)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(toml11)

add_subdirectory(server)

add_executable(nduboiServer main.cpp)

target_link_libraries(nduboiServer PRIVATE
        server
        toml11
)

target_include_directories(nduboiServer PRIVATE toml11)

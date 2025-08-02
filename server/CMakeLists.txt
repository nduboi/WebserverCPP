add_library(server
        HttpServer.cpp
        HttpServer.hpp
        Utils.cpp
        Utils.hpp
        Exception.hpp
        Router.cpp
        Router.hpp
        ALogger.cpp
        ALogger.hpp
        ServiceLogger.cpp
        ServiceLogger.hpp
        ILogger.hpp)

target_link_libraries(server PRIVATE toml11)
target_include_directories(server PRIVATE toml11)
/*
** EPITECH PROJECT, 2025
** webserverCPP
** File description:
** ILogger.cpp
*/
#ifndef ILOGGER_HPP
#define ILOGGER_HPP

namespace Logger {
    enum LogLevel {
        DEGUB,
        INFO,
        ERROR,
        FATAL
    };

    class ILogger {
    public:

        virtual void setLogLevel(LogLevel) = 0;
        virtual void debug(const std::string &msg, const std::string &service) = 0;
        virtual void info(const std::string &msg, const std::string &service) = 0;
        virtual void error(const std::string &msg, const std::string &service) = 0;
        virtual void fatal(const std::string &msg, const std::string &service) = 0;

        virtual ~ILogger() = default;
    };
}
#endif //ILOGGER_HPP

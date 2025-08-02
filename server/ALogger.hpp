/*
** EPITECH PROJECT, 2025
** webserverCPP
** File description:
** Logger.hpp
*/

#ifndef ALOGGER_HPP
#define ALOGGER_HPP
#include <fstream>
#include <string>
#include <mutex>
#include "ILogger.hpp"

namespace Logger {
    class ALogger : public ILogger {
    private:
        LogLevel _logLevel = DEGUB;
        const std::string &_filename;
        std::mutex _mtx;
        std::ofstream _logFile;

        void _write(const std::string &service, const std::string &msg, const std::string &prefix);
    public:
        void setLogLevel(LogLevel) override;
        void debug(const std::string &msg, const std::string &service) override;
        void info(const std::string &msg, const std::string &service) override;
        void error(const std::string &msg, const std::string &service) override;
        void fatal(const std::string &msg, const std::string &service) override;
        ALogger(const std::string &fileName);
        ~ALogger();
    };
}


#endif //ALOGGER_HPP

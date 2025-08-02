/*
** EPITECH PROJECT, 2025
** webserverCPP
** File description:
** ServiceLogger.hpp
*/

#ifndef SERVICELOGGER_HPP
#define SERVICELOGGER_HPP
#include <memory>

#include "ALogger.hpp"

namespace Logger {
    class ServiceLogger {
    private:
        std::shared_ptr<ALogger> _logger;
        const std::string _serviceName = "";

    public:
        void debug(const std::string &msg);
        void info(const std::string &msg);
        void error(const std::string &msg);
        void fatal(const std::string &msg);
        ServiceLogger(std::shared_ptr<ALogger>, const std::string &serviceName);
    };
}

#endif //SERVICELOGGER_HPP

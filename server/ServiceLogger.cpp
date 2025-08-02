/*
** EPITECH PROJECT, 2025
** webserverCPP
** File description:
** ServiceLogger.cpp
*/

#include "ServiceLogger.hpp"

void Logger::ServiceLogger::debug(const std::string &msg) {
    this->_logger->debug(msg, this->_serviceName);
}

void Logger::ServiceLogger::info(const std::string &msg) {
    this->_logger->info(msg, this->_serviceName);
}

void Logger::ServiceLogger::error(const std::string &msg) {
    this->_logger->error(msg, this->_serviceName);
}

void Logger::ServiceLogger::fatal(const std::string &msg) {
    this->_logger->fatal(msg, this->_serviceName);
}

Logger::ServiceLogger::ServiceLogger(std::shared_ptr<ALogger> logger, const std::string &serviceName) : _logger(logger),  _serviceName(serviceName){
}

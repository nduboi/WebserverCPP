/*
** EPITECH PROJECT, 2025
** webserverCPP
** File description:
** Logger.cpp
*/

#include "ALogger.hpp"
#include <fstream>
#include <iostream>

void Logger::ALogger::_write(const std::string &service, const std::string &msg, const std::string &prefix) {
    std::lock_guard lock(this->_mtx);
    if (this->_logFile.is_open()) {
        time_t now = time(0);
        struct tm timeinfo;
        char timestamp[80];
        localtime_r(&now, &timeinfo);
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);

        this->_logFile << "[" << timestamp << "][" << prefix << "] " << msg << std::endl;
        #ifdef _DEBUG
            std::cout << "[" << timestamp << "][" << prefix << "]" << "[" << service << "] " << msg << std::endl;
        #endif
    } else {
        std::cerr << "Failed to open log file: " << this->_filename << std::endl;
    }
}

void Logger::ALogger::setLogLevel(LogLevel level) {
    this->_logLevel = level;
}

void Logger::ALogger::debug(const std::string &msg, const std::string &service) {
    if (this->_logLevel <= DEGUB)
        this->_write(service, msg, "DEBUG");
}

void Logger::ALogger::info(const std::string &msg, const std::string &service) {
    if (this->_logLevel <= INFO)
        this->_write(service, msg, "INFO");
}

void Logger::ALogger::error(const std::string &msg, const std::string &service) {
    if (this->_logLevel <= ERROR)
        this->_write(service, msg, "ERROR");
}

void Logger::ALogger::fatal(const std::string &msg, const std::string &service) {
    if (this->_logLevel <= FATAL)
        this->_write(service, msg, "FATAL");
}

Logger::ALogger::~ALogger() {
    this->_logFile.close();
}

Logger::ALogger::ALogger(const std::string &fileName) : _filename(fileName), _logFile(this->_filename, std::ios_base::app) {
}

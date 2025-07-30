/*
** EPITECH PROJECT, 2025
** webserverCPP
** File description:
** Exception.hpp
*/

#ifndef EXCEPTION_HPP
    #define EXCEPTION_HPP
#include <exception>
#include <string>

class HeaderError : public std::exception {
private:
    const char *_msg;
public:
    HeaderError(const std::string &msg) : _msg(msg.c_str()) {};
    const char *what() const noexcept override {return this->_msg;};
};

class PermissionDenied : public std::exception {
public:
    PermissionDenied() {};
    const char *what() const noexcept override {return "";};
};

class NotFound : public std::exception {
public:
    NotFound() {};
    const char *what() const noexcept override {return "";};
};


#endif //EXCEPTION_HPP

/*
** EPITECH PROJECT, 2025
** webserverCPP
** File description:
** utils.hpp
*/

#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>
#include <vector>


class Utils {
public:
    static std::vector<std::string> splitSpace(std::string data);
    static std::string getFileContent(const std::string &filePath);
};



#endif //UTILS_HPP

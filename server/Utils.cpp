/*
** EPITECH PROJECT, 2025
** webserverCPP
** File description:
** utils.cpp
*/

#include <sstream>
#include <fstream>
#include "Exception.hpp"
#include "Utils.hpp"

std::vector<std::string> Utils::splitSpace(std::string data) {
    std::stringstream iss(data);
    std::string word;
    std::vector<std::string> result;

    while (iss >> word) {
        result.push_back(word);
    }
    return result;
}

std::string Utils::getFileContent(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open())
        throw PermissionDenied();

    std::ostringstream contentStream;
    contentStream << file.rdbuf();
    return contentStream.str();
}

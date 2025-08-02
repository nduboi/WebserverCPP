/*
** EPITECH PROJECT, 2025
** webserverCPP
** File description:
** Router.hpp
*/

#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <string>
#include <unordered_map>
#include <optional>
#include <vector>
#include <filesystem>
#include "ServiceLogger.hpp"

class Router {
private:
    std::unordered_map<std::string, std::string> _routeList;
    std::unordered_map<std::string, std::string> _folderRoutes;
    Logger::ServiceLogger _logger;
    
    bool _isValidRoute(const std::string &route) const;
    std::optional<std::string> _checkFolderRoutes(const std::string &key) const;
public:
    std::optional<std::string> askRoute(const std::string &key);
    void addRoute(const std::string &key, const std::string &file);
    void addFolder(const std::string &prefix, const std::string &folderPath);
    void removeRoute(const std::string &key);
    std::vector<std::string> getRegisteredRoutes() const;

    Router(std::shared_ptr<Logger::ALogger> logger);
    ~Router() = default;
};



#endif //ROUTER_HPP

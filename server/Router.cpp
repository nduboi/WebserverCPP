/*
** EPITECH PROJECT, 2025
** webserverCPP
** File description:
** Router.cpp
*/

#include "Router.hpp"
#include <algorithm>
#include <iostream>

Router::Router() {
}

bool Router::_isValidRoute(const std::string &route) const {
    if (route.find("..") != std::string::npos)
        return false;
    return true;
}

std::optional<std::string> Router::_checkFolderRoutes(const std::string &key) const {
    for (const auto &[prefix, folderPath] : _folderRoutes) {
        if (key.starts_with(prefix)) {
            std::string remainingPath = key.substr(prefix.length());
            if (remainingPath.starts_with("/")) {
                remainingPath = remainingPath.substr(1);
            }
            
            std::string fullPath = folderPath;
            if (!fullPath.empty() && fullPath.back() != '/') {
                fullPath += "/";
            }
            fullPath += remainingPath;
            
            // Vérifier que le fichier existe
            if (std::filesystem::exists(fullPath) && std::filesystem::is_regular_file(fullPath)) {
                return fullPath;
            }
        }
    }
    return std::nullopt;
}

std::optional<std::string> Router::askRoute(const std::string &key) {
    if (!_isValidRoute(key)) {
        std::cerr << "[Router] Route invalide détectée: " << key << std::endl;
        return std::nullopt;
    }
    auto it = _routeList.find(key);
    if (it != _routeList.end())
        return it->second;
    return _checkFolderRoutes(key);
}

void Router::addRoute(const std::string &key, const std::string &file) {
    if (!_isValidRoute(key)) {
        std::cerr << "[Router] Tentative d'ajout d'une route invalide: " << key << std::endl;
        return;
    }
    _routeList[key] = file;
    std::cout << "[Router] Route ajoutée: " << key << " -> " << file << std::endl;
}

void Router::addFolder(const std::string &prefix, const std::string &folderPath) {
    if (!_isValidRoute(prefix)) {
        std::cerr << "[Router] Tentative d'ajout d'un dossier avec préfixe invalide: " << prefix << std::endl;
        return;
    }
    
    if (!std::filesystem::exists(folderPath) || !std::filesystem::is_directory(folderPath)) {
        std::cerr << "[Router] Le dossier n'existe pas: " << folderPath << std::endl;
        return;
    }
    _folderRoutes[prefix] = folderPath;
    std::cout << "[Router] Dossier ajouté: " << prefix << "/* -> " << folderPath << std::endl;
}

void Router::removeRoute(const std::string &key) {
    auto it = _routeList.find(key);
    if (it != _routeList.end()) {
        _routeList.erase(it);
        std::cout << "[Router] Route supprimée: " << key << std::endl;
    }
}

std::vector<std::string> Router::getRegisteredRoutes() const {
    std::vector<std::string> routes;
    for (const auto &[route, file] : _routeList) {
        routes.push_back(route + " -> " + file);
    }
    for (const auto &[prefix, folder] : _folderRoutes) {
        routes.push_back(prefix + "/* -> " + folder);
    }
    return routes;
}

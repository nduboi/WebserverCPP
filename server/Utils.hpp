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
#include <toml.hpp>
#include <iostream>


class Utils {
public:
    static std::vector<std::string> splitSpace(std::string data);
    static std::string getFileContent(const std::string &filePath);
    template <typename T>
    static T getConfigValue(const std::string &key, const T &default_value, const std::string& path = "config.toml") {
        try {
            if (!std::filesystem::exists(path)) {
                std::cerr << "[Config] Fichier " << path << " introuvable. Utilisation de la valeur par défaut.\n";
                return default_value;
            }

            const auto data = toml::parse(path);

            if (!data.contains(key)) {
                std::cerr << "[Config] Clé \"" << key << "\" absente dans " << path << ". Valeur par défaut utilisée.\n";
                return default_value;
            }

            return toml::find<T>(data, key);
        } catch (const toml::type_error& e) {
            std::cerr << "[Config] Erreur de type pour \"" << key << "\": " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "[Config] Erreur lors de la lecture de \"" << path << "\": " << e.what() << "\n";
        }
        return default_value;
    }
};



#endif //UTILS_HPP

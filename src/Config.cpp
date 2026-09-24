/*
** EPITECH PROJECT, 2026
** ___ hades_town ___
** File description:
** Config.cpp
*/

#include "Config.hpp"
#include <fstream>
#include <algorithm>

void Config::configParser(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file.\n\tDefault port: " << _port << "\n\tDefault root folder: " << _root << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.starts_with("#"))
            continue;
        if (line.starts_with("port")) {
            _port = line.substr(line.find("=") + 1);
        } else if (line.starts_with("document_root")) {
            _root = line.substr(line.find("=") + 1);
        }
    }

    _port.erase(std::remove_if(_port.begin(), _port.end(), ::isspace), _port.end());
    _root.erase(std::remove_if(_root.begin(), _root.end(), ::isspace), _root.end());

    if (_port.empty() || _root.empty()) {
        std::cerr << "Error: config file is missing required fields.\n\tDefault port: " << _port << "\n\tDefault root folder: " << _root << std::endl;
    }
}
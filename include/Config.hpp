/*
** EPITECH PROJECT, 2026
** ___ hades_town ___
** File description:
** Config.hpp
*/

#pragma once

#include <string>
#include <iostream>

class Config {
    public:
        std::string _port = "8080";
        std::string _root = ".";

        Config() = default;
        ~Config() = default;

        void configParser(const std::string &filename);
};
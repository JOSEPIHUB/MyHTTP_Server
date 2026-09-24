/*
** EPITECH PROJECT, 2026
** ___ hades_town ___
** File description:
** main.cpp
*/

#include "Server.hpp"
#include "Config.hpp"
#include <cstring>
#include <iostream>

static int displayHelp()
{
    std::cout << "USAGE: ./hell [config_file]\n"
        << "\tconfig_file: path to the configuration file (default: hell.conf).\n"
        << "\tthe path must be relative, not absolute."
        << std::endl;
    return 0;
}

int main(int ac, char **av)
{
    if (ac != 2 || std::strcmp(av[1], "-h") == 0 || std::strcmp(av[1], "--help") == 0 || av[1][0] == '/')
        return displayHelp();
    if (ac > 2) {
        std::cerr << "Error: hell: too many arguments." << std::endl;
        return 84;
    }
    Config config;
    config.configParser(av[1]);
    Server server(config);
    server.start();
    server.run();
    return 0;
}

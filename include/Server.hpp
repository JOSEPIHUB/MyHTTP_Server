/*
** EPITECH PROJECT, 2026
** ___ hades_town ___
** File description:
** server.hpp
*/

#pragma once
#include <string>
#include <vector>
#include <poll.h>
#include "Config.hpp"

class Server {
    private:
        bool _is_running = true;
        int _listen_fd;
        Config _config;
        std::vector<pollfd> _fds;

    public:
        Server(Config &config);
        ~Server();

        void start();
        void shell();
        void reloadConfig(const std::string &command);
        void run();
        void newClient();
        void handleClientData(size_t index);
        void cleanFds();
};
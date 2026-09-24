/*
** EPITECH PROJECT, 2026
** ___ hades_town ___
** File description:
** server.cpp
*/

#include "Server.hpp"
#include "Request.hpp"
#include "ResponseBuilder.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>

Server::Server(Config &config) : _config(config)
{
    pollfd stdin_fd;
    stdin_fd.fd = STDIN_FILENO;
    stdin_fd.events = POLLIN;
    stdin_fd.revents = 0;

    _fds.push_back(stdin_fd);
}

Server::~Server()
{
    if (_listen_fd != -1)
        close(_listen_fd);
    if (!_fds.empty()) {
        for (const auto &fd : _fds) {
            close(fd.fd);
        }
    }
}

void Server::start()
{
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(std::stoi(_config._port));

    bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    listen(listen_fd, SOMAXCONN);

    _listen_fd = listen_fd;
    _fds.push_back({listen_fd, POLLIN, 0});
}

void Server::cleanFds()
{
    for (size_t i = 0; i < _fds.size(); ++i) {
        if (_fds[i].fd == _listen_fd) {
            _fds.erase(_fds.begin() + i);
            break;
        }
    }
    close(_listen_fd);
}

void Server::reloadConfig(const std::string &command)
{
    std::istringstream iss(command);
    std::string cmd, configFile;

    if (iss >> cmd >> configFile && configFile[0] != '/') {
        _config.configParser(configFile);
        cleanFds();
        start();
    } else {
        std::cerr << "Error: Invalid reload command. Usage: reload <config_file>\n\t!! the path must be relative, not absolute." << std::endl;
    }
}

void Server::shell()
{
    std::string command;

    std::getline(std::cin, command);
    if (command == "exit") {
        std::cout << "bye.." << std::endl;
        _is_running = false;
        return;
    } else if (command == "status") {
        std::cout << "Status: running" << std::endl;
        std::cout << "\tPort : " << _config._port << std::endl;
        std::cout << "\tRoot : " << _config._root << std::endl;
    } else if (command.starts_with("reload")) {
        std::cout << "Reloading server configuration..." << std::endl;
        reloadConfig(command);
    } else {
        std::cout << "Unknown command..\nCommands:\n\texit\n\tstatus\n\treload (config_file)" << std::endl;
    }
    std::cout << "> " << std::flush;    
}

void Server::run()
{
    std::cout << "> " << std::flush;
    while (_is_running) {
        if (poll(_fds.data(), _fds.size(), -1) < 0) {
            std::cerr << "Error: poll failed." << std::endl;
            _is_running = false;
        }

        for (size_t i = 0; i < _fds.size(); ++i) {
            if (!(_fds[i].revents & POLLIN))
                continue;

            if (_fds[i].fd == STDIN_FILENO)
                shell();
            else if (_fds[i].fd == _listen_fd)
                newClient();
            else
                handleClientData(i);
        }
    }
}

void Server::newClient()
{
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(_listen_fd, (struct sockaddr *)&client_addr, &client_len);

    if (client_fd < 0)
        return;

    _fds.push_back({client_fd, POLLIN, 0});
}

void Server::handleClientData(size_t index)
{
    char buffer[4096];
    ssize_t bytes_read = read(_fds[index].fd, buffer, sizeof(buffer));

    if (bytes_read > 0) {
        std::string request(buffer, bytes_read);
        ResponseBuilder responseBuilder(request, _config._root);
        std::string response = responseBuilder.buildResponse();
        write(_fds[index].fd, response.c_str(), response.size());
    }

    close(_fds[index].fd);
    _fds.erase(_fds.begin() + index);
}

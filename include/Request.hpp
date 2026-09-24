/*
** EPITECH PROJECT, 2026
** ___ hades_town ___
** File description:
** requestParser.hpp
*/

#pragma once
#include <string>
#include <iostream>
#include <vector>

class Request {
    public:
        std::string _method;
        std::string _path;
        std::string _version;
        std::vector<std::pair<std::string, std::string>> _headers;
        std::string _body;

        Request() = default;
        ~Request() = default;

        void requestParser(const std::string request);

    void displayRequest() const
    {
        std::cout << "Method: " << _method << " Path: " << _path << " Version: " << _version << std::endl;

        for (const auto &header : _headers) {
            std::cout << header.first << ": " << header.second << std::endl;
        }

        std::cout << "Body: " << _body << std::endl;
    }
};

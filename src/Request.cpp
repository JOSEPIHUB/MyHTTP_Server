/*
** EPITECH PROJECT, 2026
** ___ hades_town ___
** File description:
** requestParser.cpp
*/

#include "Request.hpp"
#include <sstream>

void Request::requestParser(const std::string request)
{
    std::istringstream request_stream(request);
    std::string line;
    std::getline(request_stream, line);

    std::istringstream request_line(line);
    request_line >> _method >> _path >> _version;

    while (std::getline(request_stream, line) && line != "\r") {
        auto colon_pos = line.find(':');
        if (colon_pos != std::string::npos) {
            std::string header_name = line.substr(0, colon_pos);
            std::string header_value = line.substr(colon_pos + 1);
            _headers.emplace_back(header_name, header_value);
        }
    }

    if (!request_stream)
        return;

    std::ostringstream body_stream;
    body_stream << request_stream.rdbuf();
    _body = body_stream.str();
}

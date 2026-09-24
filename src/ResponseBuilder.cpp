/*
** EPITECH PROJECT, 2026
** ___ hades_town ___
** File description:
** ResponseBuilder.cpp
*/

#include "ResponseBuilder.hpp"
#include <sstream>
#include <fstream>

ResponseBuilder::ResponseBuilder(const std::string request, const std::string root) : _root(root)
{
    _request.requestParser(request);
    _body = "<html><body><h1>OK</h1></body></html>";
}

std::string ResponseBuilder::setMessage()
{
    if (_statusCode == "200")
        return "OK";
    if (_statusCode == "400")
        return "Bad Request";
    if (_statusCode == "403")
        return "Forbidden";
    if (_statusCode == "404")
        return "Not Found";
    if (_statusCode == "405")
        return "Method Not Allowed";
    if (_statusCode == "413")
        return "Payload Too Large";
    if (_statusCode == "500")
        return "Internal Server Error";
    if (_statusCode == "501")
        return "Not Implemented";
    if (_statusCode == "505")
        return "HTTP Version Not Supported";
    return "Unknown";
}

std::string ResponseBuilder::make_response()
{
    std::string response = "HTTP/1.1 " + _statusCode;

    _statusMessage = setMessage();
    response += " " + _statusMessage + "\r\n";
    response += "Content-Type: " + _contentType + "\r\n";
    response += "Content-Length: " + std::to_string(_body.length()) + "\r\n";
    response += "\r\n";
    response += _body;
    return response;
}

std::string ResponseBuilder::buildResponse()
{
    check_method();
    check_path();
    check_version();
    check_headers();
    getContentType();
    getBody();
    return make_response();
}

void ResponseBuilder::check_method()
{
    if (_request._method == "GET" || _request._method == "HEAD")
        return;
    else if (_request._method == "POST" || _request._method == "PUT" || _request._method == "DELETE"){
        _statusCode = "501";
        return;
    } else {
        _statusCode = "405";
        return;
    }
}

void ResponseBuilder::check_path()
{
    if (_statusCode != "200")
        return;

    std::stringstream ss(_request._path);
    std::string segment;

    std::getline(ss, segment, '/');
    while (std::getline(ss, segment, '/')) {
        if (segment.empty() || segment == ".." || segment == "~") {
            _statusCode = "403";
            return;
        }
    }
    return;
}

void ResponseBuilder::check_version()
{
    if (_statusCode != "200")
        return;

    if (_request._version != "HTTP/1.1") {
        _statusCode = "505";
    }
}

void ResponseBuilder::check_headers()
{
    if (_statusCode != "200")
        return;

    for (const auto &header : _request._headers) {
        if (header.first == "Host") {
            return;
        }
    }
    _statusCode = "400";
}

void ResponseBuilder::getContentType()
{
    if (_statusCode != "200")
        return;

    std::string path = _request._path;
    size_t dotPos = path.find_last_of('.');
    if (dotPos == std::string::npos) {
        _contentType = "text/plain";
        return;
    }

    std::string extension = path.substr(dotPos);
    if (extension == ".html" || extension == ".htm") {
        _contentType = "text/html";
    } else if (extension == ".css") {
        _contentType = "text/css";
    } else if (extension == ".png") {
        _contentType = "image/png";
    } else if (extension == ".jpg" || extension == ".jpeg") {
        _contentType = "image/jpeg";
    } else {
        _contentType = "application/octet-stream";
    }
}

void ResponseBuilder::getBody()
{
    std::ifstream file(_root + _request._path);

    if (!file.is_open() && _statusCode == "200") {
        _statusCode = "404";
    }
    if (_statusCode != "200") {
        _body = "Error: " + _statusCode + " " + setMessage();
        return;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();

    _body = buffer.str();
    if (_request._method == "HEAD") {
        _body.clear();
    }
    return;
}
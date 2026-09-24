/*
** EPITECH PROJECT, 2026
** ___ hades_town ___
** File description:
** responseBuilder.hpp
*/

#pragma once
#include "Request.hpp"
#include <string>
#include <vector>

class ResponseBuilder {
    private:
        Request _request;
        std::string _statusCode = "200";
        std::string _statusMessage;
        std::string _contentType;
        std::string _body;
        std::string _root;

    public:
        ResponseBuilder(const std::string request, const std::string root);
        ~ResponseBuilder() = default;

        std::string buildResponse();
        std::string setMessage();
        std::string make_response();
        void check_method();
        void check_path();
        void check_version();
        void check_headers();
        void getContentType();
        void getBody();

        void displayResponse() const
        {
            std::cout << "Status Code: " << _statusCode << " Status Message: " << _statusMessage << std::endl;
            std::cout << "Content Type: " << _contentType << std::endl;
            std::cout << "Body: " << _body << std::endl;
        }
};
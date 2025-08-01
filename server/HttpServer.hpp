/*
** EPITECH PROJECT, 2025
** webserverCPP
** File description:
** HttpServer.hpp
*/

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <memory>

#include "Router.hpp"


class HttpServer {
public:
    enum requestType {
        GET,
        POST,
        UPDATE,
        DELETE,
        NONE
    };

private:
    unsigned int _status = 0;
    requestType _reqType = NONE;
    std::string _route = "";
    std::string _protocolVersion = "";
    const std::string &_staticRoot;
    std::shared_ptr<Router> _router;

    boost::asio::ip::tcp::socket _sock;

    void _checkFile(const std::string &filePath);
    std::string _getFileUsingRoute(const std::string &route);
    std::string _getContentType(const std::string &path);
    HttpServer::requestType _getReqType(const std::string &data);
    void _parseRequest(const std::unique_ptr<boost::asio::streambuf>& data);
public:

    HttpServer() = delete;
    HttpServer(boost::asio::ip::tcp::socket sock, const std::string &staticRoot, std::shared_ptr<Router> router);
    ~HttpServer() = default;

};



#endif //HTTPSERVER_HPP

/*
** EPITECH PROJECT, 2025
** webserverCPP
** File description:
** HttpServer.cpp
*/

#include "HttpServer.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>
#include <utility>

#include "Exception.hpp"
#include "Utils.hpp"

HttpServer::HttpServer(
    boost::asio::ip::tcp::socket sock,
    const std::string &staticRoot,
    std::shared_ptr<Router> router
) : _staticRoot(staticRoot), _router(std::move(router)), _sock(std::move(sock)) {
    try {
            std::unique_ptr<boost::asio::streambuf> buffer = std::make_unique<boost::asio::streambuf>();
            boost::system::error_code error;

            boost::asio::read_until(this->_sock, *buffer, '\n', error);

            if (error && error != boost::asio::error::eof) {
                throw boost::system::system_error(error);
            }
            this->_parseRequest(buffer);
    } catch (std::exception& e) {
        std::cerr << "Exception in session: " << e.what() << std::endl;
        std::string bufferRepo = "HTTP/1.1 500\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 14\r\n"
            "\r\nInternal Error\n";
        boost::asio::write(this->_sock, boost::asio::buffer(bufferRepo));
    }
}

HttpServer::requestType HttpServer::_getReqType(const std::string &data) {
    if (data == "GET")
        return GET;
    if (data == "POST")
        return POST;
    if (data == "UPDATE")
        return UPDATE;
    if (data == "DELETE")
        return DELETE;
    throw HeaderError("Request type unknown");
}

void HttpServer::_checkFile(const std::string &filePath) {
    if (!std::filesystem::exists(filePath))
        throw NotFound();

    if (!std::filesystem::is_regular_file(filePath)) {
        throw NotFound();
    }

    std::ifstream file(filePath);
    if (!file.is_open())
        throw PermissionDenied();
}

std::string HttpServer::_getFileUsingRoute(const std::string &route) {
    std::string cleanRoute = route;
    if (cleanRoute.starts_with("/")) {
        cleanRoute = cleanRoute.substr(1);
    }
    
    // Route par défaut pour la racine
    if (cleanRoute.empty()) {
        cleanRoute = "";
    }
    
    auto result = this->_router->askRoute(cleanRoute);
    if (!result.has_value()) {
        std::cerr << "[HttpServer] Route non trouvée: " << route << std::endl;
        throw NotFound();
    }
    
    std::cout << "[HttpServer] Route résolue: " << route << " -> " << *result << std::endl;
    return *result;
}

std::string HttpServer::_getContentType(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file)
        return "application/octet-stream";

    std::vector<unsigned char> buffer(512);
    file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
    std::streamsize bytesRead = file.gcount();
    std::string content(buffer.begin(), buffer.begin() + bytesRead);

    if (bytesRead >= 4 && buffer[0] == 0x25 && buffer[1] == 0x50 &&
        buffer[2] == 0x44 && buffer[3] == 0x46)
        return "application/pdf";

    if (bytesRead >= 3 && buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF)
        return "image/jpeg";

    if (bytesRead >= 4 && buffer[0] == 0x89 && buffer[1] == 0x50 &&
        buffer[2] == 0x4E && buffer[3] == 0x47)
        return "image/png";

    if (bytesRead >= 4 && buffer[0] == 0x47 && buffer[1] == 0x49 &&
        buffer[2] == 0x46 && buffer[3] == 0x38)
        return "image/gif";

    if (bytesRead >= 8 && buffer[4] == 'f' && buffer[5] == 't' &&
        buffer[6] == 'y' && buffer[7] == 'p')
        return "video/mp4";

    if (content.find("<svg") != std::string::npos &&
        content.find("xmlns=\"http://www.w3.org/2000/svg\"") != std::string::npos)
        return "image/svg+xml";

    if (content.find("<html") != std::string::npos)
        return "text/html";

    bool isText = true;
    for (char c : content) {
        if ((c < 32 && c != '\n' && c != '\r' && c != '\t') || c > 126) {
            isText = false;
            break;
        }
    }
    if (isText)
        return "text/plain";
    return "application/octet-stream";
}

void HttpServer::_parseRequest(const std::unique_ptr<boost::asio::streambuf>& data) {
    std::istream is(&(*data));
    std::string message;
    std::getline(is, message);

    std::vector<std::string> msgSplit = Utils::splitSpace(message);

    if (msgSplit.size() != 3)
        throw HeaderError("Wrong Header Request Size");
    this->_reqType = this->_getReqType(msgSplit[0]);
    this->_route = msgSplit[1];
    this->_protocolVersion = msgSplit[2];

    std::string filePath = this->_staticRoot;
    if (this->_staticRoot.size() > 0)
        filePath.append("/");
    std::string fileContent = "";
    try {
        filePath.append(this->_getFileUsingRoute(this->_route));
        this->_checkFile(filePath);
        this->_status = 200;
        fileContent = Utils::getFileContent(filePath);
    } catch (NotFound &) {
        this->_status = 404;
    } catch (PermissionDenied &) {
        this->_status = 403;
    }

    std::string bufferRepo = this->_protocolVersion + " " + std::to_string(this->_status) +" "+ (this->_status >= 400 ? "" : "OK") +"\r\n"
    "Content-Type: " + this->_getContentType(filePath) + "\r\n"
    "Content-Length: "+std::to_string(fileContent.size())+"\r\n"
    "\r\n"+
    fileContent;

    if (this->_status >= 400) {
        std::string errorMessage;
        switch (this->_status) {
            case 403:
                errorMessage = "403 Forbidden";
                break;
            case 404:
                errorMessage = "404 Not Found";
                break;
            case 500:
                errorMessage = "500 Internal Server Error";
                break;
            default:
                errorMessage = std::to_string(this->_status) + " Error";
        }
        
        bufferRepo = this->_protocolVersion + " " + std::to_string(this->_status) + " " + errorMessage + "\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: " + std::to_string(errorMessage.length() + 50) + "\r\n"
        "\r\n<html><body><h1>" + errorMessage + "</h1><p>La ressource demandée n'est pas disponible.</p></body></html>";
    }

    boost::asio::write(this->_sock, boost::asio::buffer(bufferRepo));
}




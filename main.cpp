#include <iostream>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "server/HttpServer.hpp"
#include "server/Utils.hpp"

int main() {
    try {
        boost::asio::io_context io_context;
        unsigned int port = Utils::getConfigValue("port", 8080);
        std::string static_root = Utils::getConfigValue<std::string>("static_root", "./www");
        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));

        std::cout << "Serveur TCP démarré sur le port: "+ std::to_string(port) +". En attente de connexions..." << std::endl;

        for (;;) {
            boost::asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);
            HttpServer(std::move(socket), static_root);
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}

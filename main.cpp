#include <iostream>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "server/HttpServer.hpp"

int main() {
    try {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 12345));

        std::cout << "Serveur TCP démarré. En attente de connexions..." << std::endl;

        for (;;) {
            boost::asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);
            HttpServer(std::move(socket));
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}

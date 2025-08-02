#include <iostream>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "server/HttpServer.hpp"
#include "server/ALogger.hpp"
#include "server/Utils.hpp"

int main() {
    try {
        boost::asio::io_context io_context;
        unsigned int port = Utils::getConfigValue("port", 8080);
        std::string LogFile = Utils::getConfigValue<std::string>("log_file", "app.log");
        unsigned int LogLevel = Utils::getConfigValue<unsigned int>("log_level", 0);
        std::string static_root = Utils::getConfigValue<std::string>("static_root", "./www");
        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));

        auto logger = std::make_shared<Logger::ALogger>(LogFile);
        logger->setLogLevel(static_cast<Logger::LogLevel>(LogLevel));
        auto mainLog = Logger::ServiceLogger(logger, "MAIN");
        auto router = std::make_shared<Router>(logger);

        mainLog.info("Serveur TCP démarré sur le port: "+ std::to_string(port) +". En attente de connexions...");

        router->addRoute("", "www/index.html");
        router->addRoute("test", "www/test.html");
        router->addFolder("www", "www");
        router->addFolder("static", "www");

        mainLog.info("Routes configurées:");
        for (const auto& route : router->getRegisteredRoutes())
            mainLog.info(route);
        for (;;) {
            boost::asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);
            HttpServer(std::move(socket), static_root, router);
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}

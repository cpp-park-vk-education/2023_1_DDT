#ifndef APP_HTTPSERVER_HTTPSERVER_HTTPSERVER_H_
#define APP_HTTPSERVER_HTTPSERVER_HTTPSERVER_H_

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include "HttpConnection.h"
#include "Router.h"

class HttpServer : private boost::noncopyable {
 public:
    HttpServer(const std::string& address, const std::string& port, std::size_t thread_pool_size);
    void run();
 private:
    void startAccept();
    void handleAccept(const boost::system::error_code& e);
    void handleStop();

    std::size_t thread_pool_size;
    boost::asio::io_service io_service;
    boost::asio::signal_set signals;
    boost::asio::ip::tcp::acceptor acceptor;
    std::shared_ptr<HttpConnection> connection;
};


#endif  // APP_HTTPSERVER_HTTPSERVER_HTTPSERVER_H_

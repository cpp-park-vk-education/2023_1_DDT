#include "HttpServer.h"

#include <vector>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

HttpServer::HttpServer(const std::string& address, const std::string& port, std::size_t thread_pool_size)
        : thread_pool_size(thread_pool_size),
          signals(io_service),
          acceptor(io_service),
          connection() {}

void HttpServer::run() {}

void HttpServer::startAccept() {}

void HttpServer::handleAccept(const boost::system::error_code& e) {}

void HttpServer::handleStop() {}

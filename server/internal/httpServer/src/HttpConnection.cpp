#include "HttpConnection.h"

#include <boost/bind.hpp>

HttpConnection::HttpConnection(boost::asio::io_service& io_service)
        : strand(io_service),
          socket(io_service) {}

boost::asio::ip::tcp::socket& HttpConnection::getSocket() {}

void HttpConnection::start() {}

void HttpConnection::handleRead(const boost::system::error_code& e,
                                std::size_t bytes_transferred) {}

void HttpConnection::handleWrite(const boost::system::error_code& e) {}

#ifndef APP_HTTPSERVER_HTTPSERVER_HTTPCONNECTION_H_
#define APP_HTTPSERVER_HTTPSERVER_HTTPCONNECTION_H_


#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

#include "Response.h"
#include "Request.h"
#include "Router.h"
#include "Parser.h"

class HttpConnection : public std::enable_shared_from_this<HttpConnection>,
                       private boost::noncopyable {
 public:
    explicit HttpConnection(boost::asio::io_service& io_service);
    boost::asio::ip::tcp::socket& getSocket();
    void start();
 protected:
    void handleRead(const boost::system::error_code& e,
                    std::size_t bytes_transferred);
    void handleWrite(const boost::system::error_code& e);

    boost::asio::io_service::strand strand;
    boost::asio::ip::tcp::socket socket;
    std::shared_ptr<Router> router;
    std::array<char, 100000> buffer{};
    Request request;
    Parser parser;
    Response response;
};

#endif  // APP_HTTPSERVER_HTTPSERVER_HTTPCONNECTION_H_

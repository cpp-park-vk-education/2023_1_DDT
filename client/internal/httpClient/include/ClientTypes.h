#ifndef APP_HTTPCLIENT_HTTPCLIENT_CLIENTTYPES_H_
#define APP_HTTPCLIENT_HTTPCLIENT_CLIENTTYPES_H_

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <boost/beast.hpp>

using Response = boost::beast::http::response<boost::beast::http::dynamic_body>;
using Request = boost::beast::http::request<boost::beast::http::string_body>;

using Params = std::map<std::string, std::string>;

struct Header {
    std::string name;
    std::string values;
};

struct ResponseStruct {
    unsigned int status;
    std::string body;
    std::vector<Header> headers;
};

struct Host {
    std::string domain;
    std::string ip;
    unsigned short port;
    Host(std::string domain, std::string ip, unsigned short port)
            : domain(std::move(domain)), ip(std::move(ip)), port(port) {}
};

#endif  // APP_HTTPCLIENT_HTTPCLIENT_CLIENTTYPES_H_

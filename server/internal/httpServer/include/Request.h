#ifndef APP_HTTPSERVER_HTTPSERVER_REQUEST_H_
#define APP_HTTPSERVER_HTTPSERVER_REQUEST_H_

#include <string>
#include <vector>

#include "Header.h"

struct Request {
    std::string method;
    std::string uri;
    int http_version_major;
    int http_version_minor;
    std::vector<Header> headers;
};

#endif  // APP_HTTPSERVER_HTTPSERVER_REQUEST_H_

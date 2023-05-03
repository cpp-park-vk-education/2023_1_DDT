#include "httpClient.h"

#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <boost/lexical_cast.hpp>
#include <boost/system/error_code.hpp>

using Error = boost::system::system_error;

std::string HttpClient::createURL(const std::string& target, const std::shared_ptr<Params>& params) {}

bool HttpClient::connect(unsigned short port = 80) {}

HttpClient::HttpClient() : socket(context), resolver(context) {}

ResponseStruct HttpClient::makeRequest(const Host &host, const std::string &target,
                                       const boost::beast::http::verb method,
                                       const std::shared_ptr<Params>& params,
                                       const std::shared_ptr<Params>& body,
                                       const std::shared_ptr<Params>& headers) {}

ResponseStruct HttpClient::parseResponse(Response response) {}

ResponseStruct HttpClient::makeGetRequest(const Host &host, const std::string &target,
                                          const std::shared_ptr<Params>& params,
                                          const std::shared_ptr<Params>& headers) {}

ResponseStruct HttpClient::makePostRequest(const Host &host, const std::string &target,
                                           const std::shared_ptr<Params>& body,
                                           const std::shared_ptr<Params>& headers) {}

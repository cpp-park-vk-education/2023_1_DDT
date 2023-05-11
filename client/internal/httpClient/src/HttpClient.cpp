#include "httpClient.h"

#include <string>
#include <boost/system/error_code.hpp>

HttpClient::HttpClient(std::string_view host_, std::string_view port) :
        host(host_),
        resolver(io_context),
        stream(io_context) {
    auto const results = resolver.resolve(host, port);
    stream.connect(results);
}

http::response<http::dynamic_body> HttpClient::makeRequest(std::string_view target,
                                                           http::verb method,
                                                           std::string_view body) {
    http::request<http::string_body> req{http::verb::get, target, 10};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    http::write(stream, req);

    beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    http::read(stream, buffer, res);

    return res;
}

http::response<http::dynamic_body> HttpClient::makeGetRequest(std::string_view target,
                                          std::string_view body) {
    return makeRequest(target, http::verb::get, body);
}

http::response<http::dynamic_body> HttpClient::makePostRequest(std::string_view target,
                                           std::string_view body) {
    return makeRequest(target, http::verb::post, body);
}

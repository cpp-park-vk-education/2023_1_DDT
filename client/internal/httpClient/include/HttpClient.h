#ifndef APP_HTTPCLIENT_HTTPCLIENT_HTTPCLIENT_H_
#define APP_HTTPCLIENT_HTTPCLIENT_HTTPCLIENT_H_

#include <utility>
#include <memory>
#include <string>
#include <boost/asio.hpp>

#include "ClientTypes.h"
#include "Serializer.h"
#include "IHttpClient.h"

class HttpClient : public IHttpClient {
 public:
    HttpClient();
    ResponseStruct makeGetRequest(const Host& host, const std::string& target,
                                  const std::shared_ptr<Params>& params = nullptr,
                                  const std::shared_ptr<Params>& headers = nullptr) override;
    ResponseStruct makePostRequest(const Host& host, const std::string& target,
                                   const std::shared_ptr<Params>& body,
                                   const std::shared_ptr<Params>& headers = nullptr) override;

 private:
    ResponseStruct parseResponse(Response response) override;
    std::string createURL(const std::string& target, const std::shared_ptr<Params>& params = nullptr) override;
    bool connect(unsigned short port) override;
    ResponseStruct makeRequest(const Host& host, const std::string& target, boost::beast::http::verb method,
                               const std::shared_ptr<Params>& params = nullptr,
                               const std::shared_ptr<Params>& body = nullptr,
                               const std::shared_ptr<Params>& headers = nullptr) override;

    boost::asio::io_context context;
    boost::asio::ip::tcp::resolver resolver;
    boost::asio::ip::tcp::socket socket;
    std::string ip;
    boost::beast::flat_buffer flat_buffer;
    Serializer serializer;
};


#endif  // APP_HTTPCLIENT_HTTPCLIENT_HTTPCLIENT_H_

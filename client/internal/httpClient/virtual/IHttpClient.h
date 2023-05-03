#ifndef APP_HTTPCLIENT_HTTPCLIENT_IHTTPCLIENT_H_
#define APP_HTTPCLIENT_HTTPCLIENT_IHTTPCLIENT_H_

#include <utility>
#include <memory>
#include <string>
#include <boost/asio.hpp>

#include "clientTypes.h"
#include "serializer.h"

class IHttpClient {
public:
    virtual ResponseStruct makeGetRequest(const Host& host, const std::string& target,
                                  const std::shared_ptr<Params>& params = nullptr,
                                  const std::shared_ptr<Params>& headers = nullptr) = 0;
    virtual ResponseStruct makePostRequest(const Host& host, const std::string& target,
                                   const std::shared_ptr<Params>& body,
                                   const std::shared_ptr<Params>& headers = nullptr) = 0;

protected:
    virtual ResponseStruct parseResponse(Response response) = 0;
    virtual std::string createURL(const std::string& target, const std::shared_ptr<Params>& params = nullptr) = 0;
    virtual bool connect(unsigned short port) = 0;
    virtual ResponseStruct makeRequest(const Host& host, const std::string& target, boost::beast::http::verb method,
                               const std::shared_ptr<Params>& params = nullptr,
                               const std::shared_ptr<Params>& body = nullptr,
                               const std::shared_ptr<Params>& headers = nullptr) = 0;
};


#endif  // APP_HTTPCLIENT_HTTPCLIENT_HTTPCLIENT_H_

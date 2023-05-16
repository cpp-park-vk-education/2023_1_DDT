#ifndef APP_HTTPSERVER_HTTPSERVER_MANAGERS_SolutionMANAGER_H_
#define APP_HTTPSERVER_HTTPSERVER_MANAGERS_SolutionMANAGER_H_

#include <memory>
#include <string>
#include <boost/beast.hpp>

#include "Serializer.h"
#include "ISolutionManager.h"
#include "SolutionService.h"

namespace beast = boost::beast;
namespace http = boost::beast::http;

class SolutionManager : public ISolutionManager {
 public:
    SolutionManager();
    http::message_generator getAllSolutions(http::request<http::string_body>&& req) override;
    http::message_generator createSolution(http::request<http::string_body>&& req) override;
    void setService(std::shared_ptr<ISolutionService> service);

 private:
    std::shared_ptr<ISolutionService> solutionService;
    std::shared_ptr<Serializer> serializer;
};

#endif  // APP_HTTPSERVER_HTTPSERVER_MANAGERS_SolutionMANAGER_H_

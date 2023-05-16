#ifndef SOURCEDOUT_HTTPSERVER_ROUTER_UTILS_H
#define SOURCEDOUT_HTTPSERVER_ROUTER_UTILS_H

#include <string>
#include <memory>
#include <boost/noncopyable.hpp>
#include <boost/beast.hpp>

#include "SolutionManager.h"
#include "UserManager.h"
#include "TaskManager.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

class Router : public std::enable_shared_from_this<Router> {
 public:
    explicit Router(std::string_view doc_root_);

    http::message_generator handleRequest(http::request<http::string_body>&& req);

    void setSolutionManager(std::shared_ptr<ISolutionManager> mng) {
        solutionManager = mng;
    }
    void setUserManager(std::shared_ptr<IUserManager> mng) {
        userManager = mng;
    }
    void setTaskManager(std::shared_ptr<ITaskManager> mng) {
        taskManager = mng;
    }
 private:
    std::shared_ptr<ISolutionManager> solutionManager;
    std::shared_ptr<IUserManager> userManager;
    std::shared_ptr<ITaskManager> taskManager;
    std::string doc_root;

    http::response<http::string_body> getBadRequest(const http::request<http::string_body>& request,
                                                    beast::string_view why);
};


#endif  // SOURCEDOUT_HTTPSERVER_ROUTER_UTILS_H

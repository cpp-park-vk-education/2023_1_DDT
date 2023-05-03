#ifndef APP_HTTPSERVER_HTTPSERVER_ROUTER_H_
#define APP_HTTPSERVER_HTTPSERVER_ROUTER_H_

#include <string>
#include <memory>
#include <boost/noncopyable.hpp>

#include "SolutionManager.h"
#include "UserManager.h"
#include "TaskManager.h"
#include "Response.h"
#include "Request.h"

class Router : private boost::noncopyable {
 public:
    Router();
    void handleRequest(const Request& req, Response& res);
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
    static bool decodeUrl(const std::string& in, std::string& out);
};


#endif  // APP_HTTPSERVER_HTTPSERVER_ROUTER_H_

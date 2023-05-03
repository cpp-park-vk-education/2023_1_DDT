#ifndef APP_HTTPSERVER_HTTPSERVER_MANAGERS_USERMANAGER_H_
#define APP_HTTPSERVER_HTTPSERVER_MANAGERS_USERMANAGER_H_

#include <memory>
#include <string>

#include "Response.h"
#include "Request.h"
#include "Serializer.h"
#include "IUserManager.h"
#include "IUserService.h"

class UserManager : public IUserManager {
 public:
    UserManager();
    Response loginUser(const Request &req) override;
    Response registerUser(const Request &req) override;
    void setService(std::shared_ptr<IUserService> service);
 private:
    std::shared_ptr<IUserService> userService;
    std::shared_ptr<Serializer> serializer;
    static std::string getParam(const std::string& path, const std::string& name);
};

#endif  // APP_HTTPSERVER_HTTPSERVER_MANAGERS_USERMANAGER_H_

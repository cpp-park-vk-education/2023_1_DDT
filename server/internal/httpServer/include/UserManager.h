#ifndef APP_HTTPSERVER_HTTPSERVER_MANAGERS_USERMANAGER_H_
#define APP_HTTPSERVER_HTTPSERVER_MANAGERS_USERMANAGER_H_

#include <memory>
#include <string>

#include "Serializer.h"
#include "IUserManager.h"
#include "IUserService.h"

class UserManager : public IUserManager {
 public:
    UserManager();
    http::message_generator loginUser(http::request<http::string_body>&& req) override;
    http::message_generator registerUser(http::request<http::string_body>&& req) override;
    void setService(std::shared_ptr<IUserService> service);
 private:
    std::shared_ptr<IUserService> userService;
    std::shared_ptr<Serializer> serializer;

    // for tests with client
    int count = 0;
    std::vector<User> users;
};

#endif  // APP_HTTPSERVER_HTTPSERVER_MANAGERS_USERMANAGER_H_

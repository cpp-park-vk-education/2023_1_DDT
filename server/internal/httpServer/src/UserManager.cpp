#include "UserManager.h"

#include "TmpUserService.h"

UserManager::UserManager() : serializer(std::make_shared<Serializer>()) {}

void UserManager::setService(std::shared_ptr<IUserService> service) {
    userService = service;
}

http::message_generator UserManager::loginUser(http::request <http::string_body> &&req) {

    std::string login, password;
    std::tie(login, password) = serializer->deserialUserData(req.body());
    auto result = TmpUserService::login(login, password);
    if (result.second) {
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = serializer->serialUserData(result.first);
        res.prepare_payload();
        return res;
    } else {
        http::response<http::string_body> res{http::status::not_found, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = serializer->serialUserData(result.first);
        res.prepare_payload();
        return res;
    }
}

http::message_generator UserManager::registerUser(http::request <http::string_body> &&req) {
    std::string login, password, username;
    std::tie(login, password, username) = serializer->deserialNewUserData(req.body());
//    User user = userService->createUser(login, username, password);
    User user = TmpUserService::registerUser(login, password, username);
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/plain");
    res.keep_alive(req.keep_alive());
    res.body() = serializer->serialUserData(user);
    res.prepare_payload();
    return res;
}

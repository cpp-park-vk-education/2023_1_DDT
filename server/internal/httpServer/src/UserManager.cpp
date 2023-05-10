#include "UserManager.h"

UserManager::UserManager() : serializer(std::make_shared<Serializer>()) {}

void UserManager::setService(std::shared_ptr<IUserService> service) {
    userService = service;
}

http::message_generator UserManager::loginUser(http::request <http::string_body> &&req) {

    std::string login, password;
    std::tie(login, password) = serializer->deserialUserData(req.body());
    /// TODO

    auto const bad_request =
            [&req](beast::string_view why)
            {
                http::response<http::string_body> res{http::status::bad_request, req.version()};
                res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
                res.set(http::field::content_type, "text/html");
                res.keep_alive(req.keep_alive());
                res.body() = std::string(why);
                res.prepare_payload();
                return res;
            };

    return bad_request("123");
}

http::message_generator UserManager::registerUser(http::request <http::string_body> &&req) {
    std::string login, password, username;
    std::tie(login, password, username) = serializer->deserialNewUserData(req.body());
    User user = userService->createUser(login, username, password);
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/plain");
    res.keep_alive(req.keep_alive());
    res.body() = std::to_string(user.getId());
    res.prepare_payload();
    return res;
}

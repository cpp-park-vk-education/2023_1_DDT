#include "UserManager.h"

UserManager::UserManager() : serializer(std::make_shared<Serializer>()) {}

void UserManager::setService(std::shared_ptr<IUserService> service) {
    userService = service;
}

http::message_generator UserManager::loginUser(http::request <http::string_body> &&req) {

    std::string login, password;
    std::tie(login, password) = serializer->deserialUserData(req.body());
    bool found = false;
    User user;
    for (const auto& i : users) {
        if (i.getPassword() == password && i.getLogin() == login && !found) {
            user = i;
            found = true;
        }
    }
    if (found) {
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = serializer->serialUserData(user);
        res.prepare_payload();
        return res;
    } else {
        http::response<http::string_body> res{http::status::not_found, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = serializer->serialUserData(user);
        res.prepare_payload();
        return res;
    }
}

http::message_generator UserManager::registerUser(http::request <http::string_body> &&req) {
    std::string login, password, username;
    std::tie(login, password, username) = serializer->deserialNewUserData(req.body());
//    User user = userService->createUser(login, username, password);
    count++;
    User user = User(count, login, password, username);
    std::cout << user << std::endl;
    users.push_back(user);
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/plain");
    res.keep_alive(req.keep_alive());
    res.body() = serializer->serialUserData(user);
    res.prepare_payload();
    return res;
}

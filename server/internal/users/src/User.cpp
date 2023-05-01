#include <iostream>
#include "../User.hpp"

User::User(size_t id_, std::string login_, std::string password_, std::string username_) :
        id(id_), login(std::move(login_)), password(std::move(password_)), username(std::move(username_)) {
}
User::User(std::string login_, std::string password_, std::string username_) :
id(0), login(std::move(login_)), password(std::move(password_)), username(std::move(username_)) {
}

const std::string &User::getLogin() const {
    return login;
}

void User::setLogin(const std::string &login_) {
    User::login = login_;
}

const std::string &User::getPassword() const {
    return password;
}

void User::setPassword(const std::string &password_) {
    User::password = password_;
}

const std::string &User::getUsername() const {
    return username;
}

void User::setUsername(const std::string &username_) {
    User::username = username_;
}

size_t User::getId() const {
    return id;
}

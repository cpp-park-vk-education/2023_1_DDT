#ifndef SOURCEDOUT_USER_HPP

#include <iostream>
#include <utility>

#define SOURCEDOUT_USER_HPP

class User {
private:
    size_t id;
    std::string login;
    std::string password;
    std::string username;

public:
    User(size_t id_, std::string login_, std::string password_, std::string username_) :
            id(id_), login(std::move(login_)), password(std::move(password_)), username(std::move(username_)) {
    }

    User(std::string login_, std::string password_, std::string username_) :
            id(0), login(std::move(login_)), password(std::move(password_)), username(std::move(username_)) {
    }

    [[nodiscard]] size_t getId() const {
        return id;
    }


    [[nodiscard]] const std::string &getLogin() const {
        return login;
    }


    [[nodiscard]] const std::string &getPassword() const {
        return password;
    }

    void setPassword(const std::string &password_) {
        User::password = password_;
    }

    [[nodiscard]] const std::string &getUsername() const {
        return username;
    }

    void setUsername(const std::string &username_) {
        User::username = username_;
    }
};

#endif //SOURCEDOUT_USER_HPP

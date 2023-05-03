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
    User(size_t id_, std::string login_, std::string password_, std::string username_);

    User(std::string login_, std::string password_, std::string username_);

    [[nodiscard]] const std::string &getLogin() const;

    void setLogin(const std::string &login);

    [[nodiscard]] const std::string &getPassword() const;

    void setPassword(const std::string &password);

    [[nodiscard]] const std::string &getUsername() const;

    void setUsername(const std::string &username);

    [[nodiscard]] size_t getId() const;

    friend std::ostream &operator<<(std::ostream &os, const User &user);

    void setId(size_t id);

    bool operator==(const User &rhs) const;

    bool operator!=(const User &rhs) const;
};

#endif //SOURCEDOUT_USER_HPP

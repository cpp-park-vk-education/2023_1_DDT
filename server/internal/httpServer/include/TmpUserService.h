#pragma once

#include <vector>
#include <string>
#include "User.hpp"

class TmpUserService {
public:
    static std::pair<User, bool> login(std::string_view login, std::string_view password) {
        bool found = false;
        User user;
        for (const auto& i : tasks) {
            if (i.getPassword() == password && i.getLogin() == login && !found) {
                user = i;
                found = true;
            }
        }
        return {user, found};
    }

    static User registerUser(std::string login, std::string password, std::string username) {
        count++;
        User user(count, login, password, username);
        std::cout << user << std::endl;
        tasks.push_back(user);
        return user;
    }

    static std::size_t count;
    static std::vector<User> tasks;
};

std::vector<User> TmpUserService::tasks = {};
std::size_t TmpUserService::count = 0;

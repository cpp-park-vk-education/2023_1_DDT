#pragma once

#include <string>
#include <vector>

#include "Task.h"

class Core {
public:
    Core() { user_id = -1; };

    static unsigned signUp(const std::string &login, const std::string &username, const std::string &pass);

    static unsigned login(const std::string &login, const std::string &pass);

    static void logout();

private:
    static std::size_t user_id;
};

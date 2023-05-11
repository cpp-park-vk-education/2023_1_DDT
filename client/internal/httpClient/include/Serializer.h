#pragma once

#include <vector>
#include <memory>
#include <string>
#include "User.h"

class Serializer {
public:
    std::string serialLoginData(std::string_view login, std::string_view password);
    std::string serialRegisterData(std::string_view login, std::string_view username, std::string_view password);
    User deserialUserData(std::string_view body);
};


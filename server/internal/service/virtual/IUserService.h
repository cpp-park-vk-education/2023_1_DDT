#pragma once

#include <vector>

#include "User.hpp"

class IUserService {
 public:
  virtual User createUser(std::string login, std::string username,
                          std::string password) = 0;
  virtual User getUserById(size_t id) = 0;
  virtual void deleteUser(size_t id) = 0;
};

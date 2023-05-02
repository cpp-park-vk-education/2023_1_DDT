#pragma once

#include "User.hpp"

class UserValidator {
 private:
  User user;
  bool validateLogin();
  bool validatePassword();
  bool validateUsername();

 public:
  explicit UserValidator(User user);
  bool validateUser();
  ~UserValidator();
};

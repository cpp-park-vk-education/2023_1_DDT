#pragma once

#include "User.h"

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

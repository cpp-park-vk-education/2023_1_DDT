#include "UserValidator.h"

#include <iostream>

UserValidator::UserValidator(User user) : user(user) {}

bool UserValidator::validateUser() {
  if (validateLogin() && validatePassword() && validateUsername()) {
    return true;
  }
  return false;
}

bool UserValidator::validateLogin() {
  std::string login = user.getLogin();
  if (login.length() < 3 || login.length() > 30) {
    return false;
  }
  return true;
}

bool UserValidator::validatePassword() {
  std::string password = user.getPassword();
  if (password.length() < 8 || password.length() > 30) {
    return false;
  }
  return true;
}

bool UserValidator::validateUsername() {
  std::string username = user.getUsername();
  if (username.length() < 3 || username.length() > 20) {
    return false;
  }
  return true;
}

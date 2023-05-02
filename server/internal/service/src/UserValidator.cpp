#include "UserValidator.h"

UserValidator::UserValidator(User user) : user(user) {}

bool UserValidator::validateUser() { return true; }

bool UserValidator::validateLogin() { return true; }

bool UserValidator::validatePassword() { return true; }

bool UserValidator::validateUsername() { return true; }

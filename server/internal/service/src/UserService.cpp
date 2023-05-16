#include "UserService.h"

#include "Exceptions.h"
#include "UserValidator.h"

UserService::UserService(std::unique_ptr<IUserRepository> userRepo)
    : userRepo(std::move(userRepo)) {}


User UserService::createUser(const std::string& login, const std::string& username,
                             const std::string& password) {
  User user = User(login, password, username);
  if (!UserValidator::validate(user)) {
    throw ValidateException("invalid user params");
  }
  try {
    size_t id = userRepo->makeUser(user);
    user.setId(id);
    return user;
  } catch (...) {
    throw;
  }
}

User UserService::login(const std::string& login, const std::string& password) {
  try {
    User u = userRepo->getUserByLogin(login).value();
    if (u.getPassword() != password){
      throw LoginException("incorrect password");
    }
    return u;
  } catch (...) {
    throw;
  }
}


void UserService::deleteUser(size_t id) {
  try {
    userRepo->deleteByUserId(id);
  } catch (...) {
    throw;
  }
}

#include "UserService.h"

#include "Exeptions.h"
#include "UserRepository.hpp"

UserService::UserService()
    : userRepo(std::make_unique<UserRepository>()) {
}

User UserService::createUser(std::string login, std::string username,
                             std::string password) {
  if (login == "") {
    throw ValidateExeption("invalid login");
  }
  size_t id = userRepo->makeUser(User(login, password, username));
  return User(id, login, password, username);
}

User UserService::getUserById(size_t id) { return userRepo->getUserById(id); }

void UserService::deleteUser(size_t id) { userRepo->deleteByUserId(id); }

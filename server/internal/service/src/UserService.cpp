#include "UserService.h"

UserService::UserService(std::unique_ptr<IUserRepository> userRepo)
    : userRepo(std::move(userRepo)) {}

User UserService::createUser(std::string login, std::string username,
                             std::string password) {
  return User();
}

User UserService::getUserById(size_t id) { return User(); }

void UserService::deleteUser(size_t id) {}

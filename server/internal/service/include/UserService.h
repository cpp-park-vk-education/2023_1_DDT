#pragma once
#include <memory>

#include "IUserRepository.hpp"
#include "IUserService.h"
#include "UserValidator.h"

class UserService : IUserService {
 private:
  std::unique_ptr<IUserRepository> userRepo = std::make_unique<UserRepository>();

 public:
  ~UserService() override = default;
  explicit UserService();
  User createUser(std::string login, std::string username,
                  std::string password) override;
  User getUserById(size_t id) override;
  void deleteUser(size_t id) override;
};

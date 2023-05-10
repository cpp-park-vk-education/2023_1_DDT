#pragma once
#include <memory>

#include "IUserRepository.hpp"
#include "IUserService.h"
#include "UserValidator.h"

class UserService : IUserService {
 private:
  std::unique_ptr<IUserRepository> userRepo;

 public:
  ~UserService() override = default;
  explicit UserService(std::unique_ptr<IUserRepository> userRepo);
  UserService();
  User createUser(const std::string& login, const std::string& username,
                  const std::string& password) override;
  User getUserById(size_t id) override;
  void deleteUser(size_t id) override;
};

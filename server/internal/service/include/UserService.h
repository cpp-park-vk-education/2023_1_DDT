#pragma once
#include <memory>

#include "IUserRepository.h"
#include "IUserService.h"
#include "UserValidation.h"

class UserService : IUserService {
 private:
  std::unique_ptr<IUserRepository> userRepo;

 public:
  explicit UserService(std::unique_ptr<IUserRepository> userRepo);
  User createUser(std::string login, std::string username,
                  std::string password) override;
  User getUserById(size_t id) override;
  void deleteUser(size_t id) override;
};

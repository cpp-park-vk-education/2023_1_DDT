#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "UserValidator.h"

TEST(UserValidatorTest, validateOK) {
  UserValidator uv(User("login", "password", "username"));
  EXPECT_TRUE(uv.validateUser());
}

TEST(UserValidatorTest, invalidLogin) {
  UserValidator uv(User("", "password", "username"));
  EXPECT_FALSE(uv.validateUser());
}

TEST(UserValidatorTest, invalidPassword) {
  UserValidator uv(User("login", "", "username"));
  EXPECT_FALSE(uv.validateUser());
}

TEST(UserValidatorTest, invalidUsername) {
  UserValidator uv(User("login", "password", ""));
  EXPECT_FALSE(uv.validateUser());
}

TEST(UserValidatorTest, invalidUserFields) {
  UserValidator uv(User("", "", ""));
  EXPECT_FALSE(uv.validateUser());
}
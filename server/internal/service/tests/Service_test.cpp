#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "Exeptions.h"
#include "TaskService.h"
#include "UserService.h"

bool operator==(Task t1, Task t2) { return t1.getId() == t2.getId(); }

class Exception : public std::exception {
  std::string _msg;

 public:
  Exception(const std::string& msg) : _msg(msg) {}
  virtual const char* what() const noexcept override { return _msg.c_str(); }
};

class TaskRepositoryMock : public ITaskRepository {
 public:
  ~TaskRepositoryMock() override = default;
  MOCK_METHOD(Task, getTaskById, (size_t id), (override));
  MOCK_METHOD(void, updateTask, (Task task), (override));
  MOCK_METHOD(int, storeTask, (Task task), (override));
  MOCK_METHOD(void, deleteTask, (Task task), (override));
  MOCK_METHOD(void, deleteTaskById, (size_t id), (override));
};

struct TaskServiceTest : public testing::Test {
  TaskService* ts;
  TaskRepositoryMock* mock_ptr;

  void SetUp() {
    auto mock = std::make_unique<TaskRepositoryMock>();
    mock_ptr = mock.get();
    ts = new TaskService(std::move(mock));
  }
  void TearDown() { delete ts; }
};

ACTION(NoTaskException) { throw Exception("no task with this id in db"); }

TEST_F(TaskServiceTest, deleteTaskById) {
  EXPECT_CALL(*mock_ptr, deleteTaskById(1)).Times(1);
  ts->deleteTask(1);
}

TEST_F(TaskServiceTest, deleteTasWithInvalidId) {
  EXPECT_CALL(*mock_ptr, deleteTaskById(1))
      .Times(1)
      .WillRepeatedly(NoTaskException());
  EXPECT_THROW(ts->deleteTask(1), Exception);
}

TEST_F(TaskServiceTest, GetTaskByIdOK) {
  EXPECT_CALL(*mock_ptr, getTaskById(1))
      .Times(1)
      .WillOnce(::testing::Return(Task(1, "desription")));
  Task t = ts->getTask(1);
  EXPECT_EQ(t.getId(), 1);
  EXPECT_EQ(t.getDescription(), "desription");
}

TEST_F(TaskServiceTest, GetTaskByIdEXEPTION) {
  EXPECT_CALL(*mock_ptr, getTaskById(-1)).Times(1).WillRepeatedly(NoTaskException());
  EXPECT_THROW(ts->getTask(-1), Exception);
}

TEST_F(TaskServiceTest, CreateTask) {
  EXPECT_CALL(*mock_ptr, storeTask(Task("desc")))
      .Times(1)
      .WillOnce(::testing::Return(1));
  Task t = ts->createTask("desc");
  EXPECT_EQ(t.getId(), 1);
  EXPECT_EQ(t.getDescription(), "desc");

  EXPECT_CALL(*mock_ptr, storeTask(Task("desc2")))
      .Times(1)
      .WillOnce(::testing::Return(2));
  t = ts->createTask("desc2");
  EXPECT_EQ(t.getId(), 2);
  EXPECT_EQ(t.getDescription(), "desc2");
}

bool operator==(User u1, User u2) { return u1.getId() == u2.getId(); }

class UserRepositoryMock : public IUserRepository {
 public:
  ~UserRepositoryMock() override = default;
  MOCK_METHOD(User, getUserById, (size_t id), (override));
  MOCK_METHOD(User, getUserByLogin, (std::string login), (override));
  MOCK_METHOD(size_t, makeUser, (User user), (override));
  MOCK_METHOD(void, deleteUser, (User user), (override));
  MOCK_METHOD(void, deleteByUserId, (size_t id), (override));
  MOCK_METHOD(std::vector<User>, getAllUsers, (), (override));
};

struct UserServiceTest : public testing::Test {
  UserService* us;
  UserRepositoryMock* mock_ptr;

  void SetUp() {
    auto mock = std::make_unique<UserRepositoryMock>();
    mock_ptr = mock.get();
    us = new UserService(std::move(mock));
  }
  void TearDown() { delete us; }
};

ACTION(NoUserException) { throw Exception("no user with this id in db"); }

TEST_F(UserServiceTest, deleteUser) {
  EXPECT_CALL(*mock_ptr, deleteByUserId(1)).Times(1);
  us->deleteUser(1);
}

TEST_F(UserServiceTest, deleteUserWithInvalidId) {
  EXPECT_CALL(*mock_ptr, deleteByUserId(1))
      .Times(1)
      .WillRepeatedly(NoUserException());
  EXPECT_THROW(us->deleteUser(1), Exception);
}

TEST_F(UserServiceTest, getUserOk) {
  EXPECT_CALL(*mock_ptr, getUserById(1))
      .Times(1)
      .WillOnce(::testing::Return(User(1, "login", "password", "username")));
  User u = us->getUserById(1);
  EXPECT_EQ(u.getLogin(), "login");
  EXPECT_EQ(u.getId(), 1);
  EXPECT_EQ(u.getPassword(), "password");
  EXPECT_EQ(u.getUsername(), "username");
}

TEST_F(UserServiceTest, getUserEXEPTION) {
  EXPECT_CALL(*mock_ptr, getUserById(-1)).Times(1).WillOnce(NoUserException());
  EXPECT_THROW(us->getUserById(-1), Exception);
}

TEST_F(UserServiceTest, makeUserOk) {
  EXPECT_CALL(*mock_ptr, makeUser(User("login", "password", "username")))
      .Times(1)
      .WillOnce(::testing::Return(1));
  User u = us->createUser("login", "username", "password");
  EXPECT_EQ(u.getLogin(), "login");
  EXPECT_EQ(u.getId(), 1);
  EXPECT_EQ(u.getPassword(), "password");
  EXPECT_EQ(u.getUsername(), "username");
}

TEST_F(UserServiceTest, makeUserInvalidData) {
  EXPECT_CALL(*mock_ptr, makeUser(User("login", "password", "username")))
      .Times(0);
  EXPECT_THROW(us->createUser("", "", ""), ValidateExeption);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "TaskService.h"


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
  MOCK_METHOD(std::vector<Task>, getAllTasks,(),(override));
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
  EXPECT_THROW(ts->deleteTask(1), std::exception);
}

TEST_F(TaskServiceTest, GetTaskByIdOK) {
  EXPECT_CALL(*mock_ptr, getTaskById(1))
      .Times(1)
      .WillOnce(::testing::Return(Task(1, "desription",0.7f)));
  Task t = ts->getTask(1);
  EXPECT_EQ(t.getId(), 1);
  EXPECT_EQ(t.getDescription(), "desription");
}

TEST_F(TaskServiceTest, GetTaskByIdEXEPTION) {
  EXPECT_CALL(*mock_ptr, getTaskById(-1))
      .Times(1)
      .WillRepeatedly(NoTaskException());
  EXPECT_THROW(ts->getTask(-1), std::exception);
}

TEST_F(TaskServiceTest, CreateTask) {
  EXPECT_CALL(*mock_ptr, storeTask(Task("desc",0.5f)))
      .Times(1)
      .WillOnce(::testing::Return(1));
  Task t = ts->createTask("desc",0.5f);
  EXPECT_EQ(t.getId(), 1);
  EXPECT_EQ(t.getDescription(), "desc");

  EXPECT_CALL(*mock_ptr, storeTask(Task("desc2",0.8f)))
      .Times(1)
      .WillOnce(::testing::Return(2));
  t = ts->createTask("desc2",0.8f);
  EXPECT_EQ(t.getId(), 2);
  EXPECT_EQ(t.getDescription(), "desc2");
}

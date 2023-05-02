#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "TaskService.h"

class TaskRepositoryMock : public ITaskRepository {
 public:
  ~TaskRepositoryMock() override = default;
  MOCK_METHOD(Task, getTaskById, (size_t id), (override));
  MOCK_METHOD(void, updateTask, (Task task), (override));
  MOCK_METHOD(void, storeTask, (Task task), (override));
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
  void TearDown() {
    delete ts;
  }
};

TEST_F(TaskServiceTest, GetTask) {
  EXPECT_CALL(*mock_ptr, deleteTaskById(1));
  ts->deleteTask(1);
}

TEST_F(TaskServiceTest, Test) {
  int a = 2;
  EXPECT_EQ(a, 2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}
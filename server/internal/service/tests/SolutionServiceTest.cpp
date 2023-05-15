#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "SolutionService.h"

class Exception : public std::exception {
  std::string _msg;

 public:
  Exception(const std::string& msg) : _msg(msg) {}
  virtual const char* what() const noexcept override { return _msg.c_str(); }
};

class SolutionRepositoryMock : public ISolutionRepository {
 public:
  ~SolutionRepositoryMock() override = default;
  MOCK_METHOD(Solution, getSolutionById, (size_t id), (override));
  MOCK_METHOD(std::vector<Solution>, getSolutionsBySenderId, (size_t sender_id),
              (override));
  MOCK_METHOD(std::vector<Solution>, getSolutionsByTaskId, (size_t task_id),
              (override));
  MOCK_METHOD(std::vector<Solution>, getSolutions,
              (size_t sender_id, size_t task_id), (override));
  MOCK_METHOD(size_t, storeSolution, (Solution solution), (override));
  MOCK_METHOD(void, updateSolution, (Solution solution), (override));
  MOCK_METHOD(void, deleteSolutionById, (size_t id), (override));
  MOCK_METHOD(void, deleteSolution, (Solution solution), (override));
};

class TaskRepositoryMock : public ITaskRepository {
 public:
  ~TaskRepositoryMock() override = default;
  MOCK_METHOD(Task, getTaskById, (size_t id), (override));
  MOCK_METHOD(void, updateTask, (Task task), (override));
  MOCK_METHOD(int, storeTask, (Task task), (override));
  MOCK_METHOD(void, deleteTask, (Task task), (override));
  MOCK_METHOD(void, deleteTaskById, (size_t id), (override));
  MOCK_METHOD(std::vector<Task>, getAllTasks, (), (override));
};

struct SolutionServiceTest : public testing::Test {
  SolutionService* ss;
  SolutionRepositoryMock* solutionMockPtr;
  TaskRepositoryMock* taskMockPtr;

  void SetUp() {
    auto sMock = std::make_unique<SolutionRepositoryMock>();
    solutionMockPtr = sMock.get();
    auto tMock = std::make_unique<TaskRepositoryMock>();
    taskMockPtr = tMock.get();
    ss = new SolutionService(std::move(sMock), std::move(tMock));
  }
  void TearDown() { delete ss; }
};

ACTION(NoSolutionException) {
  throw Exception("no solution with this id in db");
}

TEST_F(SolutionServiceTest, getSolutionsByUserAndTaskId) {
  std::vector<Solution> solutions;
  solutions.push_back(Solution(0, "", 1, "", "", "", 1, ""));
  solutions.push_back(Solution(1, "", 1, "", "", "", 1, ""));
  EXPECT_CALL(*solutionMockPtr, getSolutions(1, 1))
      .Times(1)
      .WillOnce(::testing::Return(solutions));
  std::vector<Solution> sols = ss->getSolutionsByUserAndTaskId(1, 1);
  EXPECT_EQ(sols.size(), 2);
}

TEST_F(SolutionServiceTest, deleteSolution) {
  EXPECT_CALL(*solutionMockPtr, deleteSolutionById(1)).Times(1);
  ss->deleteSolutionById(1);
}

TEST_F(SolutionServiceTest, deleteSolutionException) {
  EXPECT_CALL(*solutionMockPtr, deleteSolutionById(-1))
      .Times(1)
      .WillRepeatedly(NoSolutionException());
  EXPECT_THROW(ss->deleteSolutionById(-1), std::exception);
}

TEST_F(SolutionServiceTest, getMetrics) {
  EXPECT_CALL(*solutionMockPtr, getSolutionById(1))
      .Times(1)
      .WillOnce(::testing::Return(
          Solution(1, "", 1, "", "tokens", "astTree", 1, "")));
  std::pair<std::string, std::string> metrics = ss->getMetrics(1);
  EXPECT_EQ(metrics.first, "tokens");
  EXPECT_EQ(metrics.second, "astTree");
}

TEST_F(SolutionServiceTest, getMetricsException) {
  EXPECT_CALL(*solutionMockPtr, getSolutionById(-1))
      .Times(1)
      .WillRepeatedly(NoSolutionException());
  EXPECT_THROW(ss->getMetrics(-1), std::exception);
}

TEST_F(SolutionServiceTest, createSolution) {
  EXPECT_CALL(*solutionMockPtr,
              storeSolution(Solution(0, "", 2, "source", "", "", 1, "")))
      .Times(1)
      .WillRepeatedly(::testing::Return(1));

  std::vector<Solution> solutions;
  solutions.push_back(
      Solution(0, "", 1, "int main(){return 0;}", "", "", 1, ""));
  solutions.push_back(Solution(1, "", 1, "", "", "", 1, ""));
  EXPECT_CALL(*solutionMockPtr, getSolutionsByTaskId(1))
      .Times(1)
      .WillOnce(::testing::Return(solutions));

  EXPECT_CALL(*taskMockPtr, getTaskById(1))
      .Times(1)
      .WillOnce(::testing::Return(Task(1, "desription", 0.7f)));

  Solution sol = ss->createSolution(2, 1, "main.cpp", "int main(){return 0;}");
  EXPECT_EQ(sol.getId(), 1);
  EXPECT_EQ(sol.getSource(), "int main(){return 0;}");
  EXPECT_EQ(sol.getTokens(),
            "[@0,0:2='int',<45>,1:0] [@1,4:7='main',<132>,1:4] "
            "[@2,8:8='(',<85>,1:8] [@3,9:9=')',<86>,1:9] "
            "[@4,10:10='{',<89>,1:10] [@5,11:16='return',<59>,1:11] "
            "[@6,18:18='0',<1>,1:18] [@7,19:19=';',<128>,1:19] "
            "[@8,20:20='}',<90>,1:20] [@9,21:20='<EOF>',<-1>,1:21] ");
  EXPECT_EQ(sol.getResult(), "Красивое решение. А главное уникальное !");
}
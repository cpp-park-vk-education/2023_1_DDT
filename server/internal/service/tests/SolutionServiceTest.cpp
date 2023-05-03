#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "SolutionService.h"

class Exception : public std::exception {
  std::string _msg;

 public:
  Exception(const std::string& msg) : _msg(msg) {}
  virtual const char* what() const noexcept override { return _msg.c_str(); }
};

bool operator==(Solution s1, Solution s2) { return s1.getId() == s2.getId(); }

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

struct SolutionServiceTest : public testing::Test {
  SolutionService* ss;
  SolutionRepositoryMock* mock_ptr;

  void SetUp() {
    auto mock = std::make_unique<SolutionRepositoryMock>();
    mock_ptr = mock.get();
    ss = new SolutionService(std::move(mock));
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
  EXPECT_CALL(*mock_ptr, getSolutions(1, 1))
      .Times(1)
      .WillOnce(::testing::Return(solutions));
  std::vector<Solution> sols = ss->getSolutionsByUserAndTaskId(1, 1);
  EXPECT_EQ(sols.size(), 2);
}

TEST_F(SolutionServiceTest, deleteSolution) {
  EXPECT_CALL(*mock_ptr, deleteSolutionById(1)).Times(1);
  ss->deleteSolutionById(1);
}

TEST_F(SolutionServiceTest, deleteSolutionException) {
  EXPECT_CALL(*mock_ptr, deleteSolutionById(-1))
      .Times(1)
      .WillRepeatedly(NoSolutionException());
  EXPECT_THROW(ss->deleteSolutionById(-1), std::exception);
}

TEST_F(SolutionServiceTest, getMetrics) {
  EXPECT_CALL(*mock_ptr, getSolutionById(1))
      .Times(1)
      .WillOnce(::testing::Return(
          Solution(1, "", 1, "", "tokens", "astTree", 1, "")));
  std::pair<std::string, std::string> metrics = ss->getMetrics(1);
  EXPECT_EQ(metrics.first, "tokens");
  EXPECT_EQ(metrics.second, "astTree");
}

TEST_F(SolutionServiceTest, getMetricsException) {
  EXPECT_CALL(*mock_ptr, getSolutionById(-1))
      .Times(1)
      .WillRepeatedly(NoSolutionException());
  EXPECT_THROW(ss->getMetrics(-1), std::exception);
}

TEST_F(SolutionServiceTest, createSolution) {
  EXPECT_CALL(*mock_ptr,
              storeSolution(Solution(0, "", 2, "source", "", "", 1, "")))
      .Times(1)
      .WillRepeatedly(::testing::Return(1));
  Solution sol = ss->createSolution(2, 1, "source");
  EXPECT_EQ(sol.getId(), 1);
  EXPECT_EQ(sol.getSource(), "source");
}
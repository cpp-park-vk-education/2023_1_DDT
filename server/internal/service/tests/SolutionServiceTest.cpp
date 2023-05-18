#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <istream>
#include <sstream>

#include "SolutionService.h"

class Exception : public std::exception {
    std::string _msg;

 public:
    explicit Exception(const std::string& msg) : _msg(msg) {}
    const char* what() const noexcept override { return _msg.c_str(); }
};

class SolutionRepositoryMock : public ISolutionRepository {
 public:
    ~SolutionRepositoryMock() override = default;
    MOCK_METHOD(std::optional<Solution>, getSolutionById, (size_t id), (override));
    MOCK_METHOD(std::vector<Solution>, getSolutionsBySenderId, (size_t sender_id), (override));
    MOCK_METHOD(std::vector<Solution>, getSolutionsByTaskId, (size_t task_id), (override));
    MOCK_METHOD(size_t, storeSolution, (Solution solution), (override));
    MOCK_METHOD(void, updateSolution, (Solution solution), (override));
    MOCK_METHOD(void, deleteSolutionById, (size_t id), (override));
    MOCK_METHOD(void, deleteSolution, (Solution solution), (override));
    MOCK_METHOD(std::optional<Solution>, getOriginalSolution, (size_t id), (override));
};

class TaskRepositoryMock : public ITaskRepository {
 public:
    ~TaskRepositoryMock() override = default;
    MOCK_METHOD(std::optional<Task>, getTaskById, (size_t id), (override));
    MOCK_METHOD(void, updateTask, (const Task& task), (override));
    MOCK_METHOD(size_t, storeTask, (Task task), (override));
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

ACTION(NoSolutionException) { throw Exception("no solution with this id in db"); }

TEST_F(SolutionServiceTest, deleteSolution) {
    EXPECT_CALL(*solutionMockPtr, deleteSolutionById(1)).Times(1);
    ss->deleteSolutionById(1);
}

TEST_F(SolutionServiceTest, deleteSolutionException) {
    EXPECT_CALL(*solutionMockPtr, deleteSolutionById(-1)).Times(1).WillRepeatedly(NoSolutionException());
    EXPECT_THROW(ss->deleteSolutionById(-1), std::exception);
}

TEST_F(SolutionServiceTest, getMetrics) {
    EXPECT_CALL(*solutionMockPtr, getSolutionById(1))
        .Times(1)
        .WillOnce(::testing::Return(Solution(1, "", 1, "", 1, "", "tokens", "astTree", 1)));
    std::pair<std::string, std::string> metrics = ss->getMetrics(1);
    EXPECT_EQ(metrics.first, "tokens");
    EXPECT_EQ(metrics.second, "astTree");
}

TEST_F(SolutionServiceTest, getMetricsException) {
    EXPECT_CALL(*solutionMockPtr, getSolutionById(-1)).Times(1).WillRepeatedly(NoSolutionException());
    EXPECT_THROW(ss->getMetrics(-1), std::exception);
}

TEST_F(SolutionServiceTest, createSolution) {
    EXPECT_CALL(*solutionMockPtr, storeSolution(Solution(0, "", 2, "source", 1, "", "", "", 1)))
        .Times(1)
        .WillRepeatedly(::testing::Return(1));

    std::vector<Solution> solutions;
    solutions.push_back(
        Solution(0, "", 1, "int main(){return 0;}", 1, "",
                 "9 45 132 85 86 89 78 45 132 128 45 132 101 1 128 132 127 132 103 103 132 128 84 85 132 115 1 86 89 "
                 "43 85 132 97 1 86 132 120 128 132 113 1 128 90 132 127 132 102 102 132 128 59 1 128 90 -1",
                 "", -1));
    EXPECT_CALL(*solutionMockPtr, getSolutionsByTaskId(1)).Times(1).WillOnce(::testing::Return(solutions));

    EXPECT_CALL(*taskMockPtr, getTaskById(1)).Times(1).WillOnce(::testing::Return(Task(1, "desription", 0.5f)));
    std::string line;
    // std::ifstream in("/project/server/internal/service/tests/task1.cpp"); // окрываем файл для чтения
    // std::stringstream sst;
    // sst << in.rdbuf();

    Solution sol = ss->createSolution(2, 1, "main.cpp", "int main() { return 0; }");
    EXPECT_EQ(sol.getId(), 1);
    // EXPECT_EQ(sol.getSource(), "int main(){return 0;}");
    EXPECT_EQ(sol.getTokens(),
              "9 45 132 85 86 89 78 45 132 128 45 132 101 1 128 132 127 132 103 103 132 128 84 85 132 115 1 86 89 43 "
              "85 132 97 1 86 132 120 128 132 113 1 128 90 132 127 132 102 102 132 128 59 1 128 90 -1 ");
    EXPECT_EQ(sol.getResult(), "Не, ну вы не палитесь. Плагиат.");
}

#include "SolutionService.h"

SolutionService::SolutionService(
    std::unique_ptr<ISolutionRepository> solutionRepo)
    : solutionRepo(std::move(solutionRepo)) {}

Solution SolutionService::createSolution(size_t userId, size_t taskId,
                                         std::string source) {
  return Solution();
}

std::vector<Solution> SolutionService::getSolutionsByUserAndTaskId(
    size_t userId, size_t taskId) {
  return std::vector<Solution>();
}

SolutionService::deleteSolutionById(size_t solId) {}

std::pair<std::string, std::string> Solution::getMetrics(size_t solId) {
  return std::make_pair("", "");
}

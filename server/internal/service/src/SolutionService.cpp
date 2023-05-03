#include "SolutionService.h"

SolutionService::SolutionService(
    std::unique_ptr<ISolutionRepository> solutionRepo)
    : solutionRepo(std::move(solutionRepo)) {}

Solution SolutionService::createSolution(size_t userId, size_t taskId,
                                         std::string source) {
  size_t id = solutionRepo->storeSolution(
      Solution(0, "", userId, source, "metrics1", "metrics2", taskId, ""));
  return Solution(id, "", userId, source, "", "", taskId, "");
}

std::vector<Solution> SolutionService::getSolutionsByUserAndTaskId(
    size_t userId, size_t taskId) {
  try {
    return solutionRepo->getSolutions(userId, taskId);
  } catch (std::exception& e) {
    throw e;
  }
}

void SolutionService::deleteSolutionById(size_t solId) {
  try {
    solutionRepo->deleteSolutionById(solId);
  } catch (std::exception& e) {
    throw e;
  }
}

std::pair<std::string, std::string> SolutionService::getMetrics(size_t solId) {
  try {
    Solution sol = solutionRepo->getSolutionById(solId);
    std::string tokens = sol.getTokens();
    std::string astTree = sol.getAstTree();
    return std::make_pair(tokens, astTree);
  } catch (std::exception& e) {
    throw e;
  }
}

void SolutionService::setAntlrWrapper(std::unique_ptr<IAntlrWrapper> antlr_) {
  antlr = std::move(antlr_);
}

void SolutionService::setMetrics(std::unique_ptr<IMockMetrics> metrics_) {
  metrics = std::move(metrics_);
}

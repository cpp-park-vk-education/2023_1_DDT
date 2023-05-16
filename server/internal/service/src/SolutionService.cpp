#include "SolutionService.h"

#include "SolutionRepository.hpp"

SolutionService::SolutionService()
    : solutionRepo(std::make_unique<SolutionRepository>()) {}

Solution SolutionService::createSolution(size_t userId, size_t taskId,
                                         std::string source) {
  return Solution();
}

std::vector<Solution> SolutionService::getSolutionsByUserAndTaskId(
    size_t userId, size_t taskId) {
  return std::vector<Solution>();
}

void SolutionService::deleteSolutionById(size_t solId) {}

std::pair<std::string, std::string> SolutionService::getMetrics(size_t solId) {
  return std::make_pair("", "");
}

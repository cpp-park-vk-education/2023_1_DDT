#pragma once

#include <memory>

#include "ISolutionRepository.hpp"
#include "ISolutionService.h"

class SolutionService : ISolutionService {
 private:
  std::unique_ptr<ISolutionRepository> solutionRepo;
  // std::unique_ptr<IAntlrWrapper> antlr
 public:
  explicit SolutionService();
  Solution createSolution(size_t userId, size_t taskId,
                          std::string source) override;
  std::vector<Solution> getSolutionsByUserAndTaskId(size_t userId,
                                                    size_t taskId) override;
  void deleteSolutionById(size_t solId) override;
  std::pair<std::string, std::string> getMetrics(size_t solId) override;
};

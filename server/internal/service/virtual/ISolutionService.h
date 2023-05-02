#pragma once

#include <utility>
#include <vector>

#include "Solution.hpp"

class ISolutionService {
 public:
  virtual Solution createSolution(size_t userId, size_t taskId,
                                  std::string source) = 0;
  virtual std::vector<Solution> getSolutionsByUserAndTaskId(size_t userId,
                                                            size_t taskId) = 0;
  virtual void deleteSolutionById(size_t solId) = 0;

  virtual std::pair<std::string, std::string> getMetrics(size_t solId) = 0;
};

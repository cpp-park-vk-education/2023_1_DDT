#pragma once

#include <memory>

#include "IAntlrWrapper.h"
#include "IMockMetrics.h"
#include "ISolutionRepository.hpp"
#include "ISolutionService.h"

class SolutionService : ISolutionService {
 private:
  std::unique_ptr<ISolutionRepository> solutionRepo;
  std::unique_ptr<IAntlrWrapper> antlr;
  std::unique_ptr<IMockMetrics> metrics;

 public:
  explicit SolutionService(std::unique_ptr<ISolutionRepository> solutionRepo);
  SolutionService();
  void setAntlrWrapper(std::unique_ptr<IAntlrWrapper> antlr_);
  void setMetrics(std::unique_ptr<IMockMetrics> metrics_);
  Solution createSolution(size_t userId, size_t taskId,
                          const std::string& source) override;
  std::vector<Solution> getSolutionsByUserAndTaskId(size_t userId,
                                                    size_t taskId) override;
  void deleteSolutionById(size_t solId) override;
  std::pair<std::string, std::string> getMetrics(size_t solId) override;
};

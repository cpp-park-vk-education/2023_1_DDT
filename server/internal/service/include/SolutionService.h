#pragma once

#include <memory>
#include <utility>

#include "IAntlrWrapper.h"
#include "IMetricRepository.hpp"
#include "IMockMetrics.h"
#include "ISolutionRepository.hpp"
#include "ISolutionService.h"

class SolutionService : ISolutionService {
 private:
  std::unique_ptr<ISolutionRepository> solutionRepo;
  std::unique_ptr<IMetricRepository> metricRepo;
  // taskRepo
  std::unique_ptr<IAntlrWrapper> antlr;
  std::unique_ptr<IMockMetrics> metrics;
  void setAntlrWrapper(const std::string& source, std::ifstream& in);

 public:
  explicit SolutionService(std::unique_ptr<ISolutionRepository> solutionRepo);
  SolutionService();
  void setMetrics(std::unique_ptr<IMockMetrics> metrics_);
  Solution createSolution(size_t userId, size_t taskId,
                          const std::string& source) override;
  std::vector<Solution> getSolutionsByUserAndTaskId(size_t userId,
                                                    size_t taskId) override;
  void deleteSolutionById(size_t solId) override;
  std::pair<std::string, std::string> getMetrics(size_t solId) override;
};

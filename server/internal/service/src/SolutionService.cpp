#include "SolutionService.h"

#include <chrono>

#include "MyCppAntlr.h"

SolutionService::SolutionService(
    std::unique_ptr<ISolutionRepository> solutionRepo)
    : solutionRepo(std::move(solutionRepo)) {}

SolutionService::SolutionService() {
  // solutionRepo=std::make_unique<SolutionRepository>();
  // taskRepo = std::make_unique<TaskRepository>();
  // metricRepo = std::make_unique<MetricRepository>();
}

void SolutionService::setAntlrWrapper(const std::string& source,
                                      std::ifstream& in) {
  if (source.substr(source.find_last_of(".") + 1) == "cpp") {
    antlr = std::make_unique<MyCppAntlr>(in);
  } else {
    throw "exception";
  }
}

// Вердикт функция
// treshhold хардкод

//TODO "filename" "data" - string -> создать файл 
Solution SolutionService::createSolution(size_t userId, size_t taskId,
                                         const std::string& source) {
  try {
    std::ifstream in(source);
    setAntlrWrapper(source, in);
    std::pair<std::string, std::string> codeParse = antlr->getTokensAndTree();

    std::time_t now =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    
    // TODO: вызов метрик
    // получил результат


    Solution sol = Solution(std::ctime(&now), userId, source, codeParse.first,
                            codeParse.second, taskId, "");
    size_t id = solutionRepo->storeSolution(sol);
    sol.setId(id);
    return sol;
  } catch (std::exception& e) {
    throw e;
  }
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

void SolutionService::setMetrics(std::unique_ptr<IMockMetrics> metrics_) {
  metrics = std::move(metrics_);
}

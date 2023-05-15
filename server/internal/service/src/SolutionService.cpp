#include "SolutionService.h"

#include <chrono>
#include <iostream>
#include <sstream>

#include "FileMethods.h"
#include "MyCppAntlr.h"
#include "PythonAntlr.h"

const std::string PLAGIAT_VERDICT = "Не, ну вы не палитесь. Плагиат.";
const std::string NOT_PLAGIAT_VERDICT =
    "Красивое решение. А главное уникальное !";

SolutionService::SolutionService(
    std::unique_ptr<ISolutionRepository> solutionRepo,
    std::unique_ptr<ITaskRepository> taskRepo)
    : solutionRepo(std::move(solutionRepo)), taskRepo(std::move(taskRepo)) {}

SolutionService::SolutionService() {
  // solutionRepo=std::make_unique<SolutionRepository>();
  // taskRepo = std::make_unique<TaskRepository>();
}

void SolutionService::setAntlrWrapper(const std::string& fileExtension,
                                      const std::string& filedata) {
  std::istringstream in(filedata);
  if (fileExtension == CPP_EXTENSION) {
    antlr = std::make_unique<MyCppAntlr>(in);
  } else if (fileExtension == PYTHON_EXTENSION) {
    antlr = std::make_unique<PythonAntlr>(in);
  }
}

std::string SolutionService::setResultVerdict(float textBasedRes,
                                              float tokenBasedRes,
                                              float treshold = 0.5f) {
  float meanRes = (tokenBasedRes + textBasedRes) / 2;
  if (meanRes < treshold) {
    return NOT_PLAGIAT_VERDICT;
  }
  return PLAGIAT_VERDICT;
}

// std::pair<float, size_t> SolutionService::getMaxTextResMetric(
//     std::vector<Solution>& solutions, const std::string& filedata,
//     float treshold) {
//   std::pair<float, size_t> maxMatch = std::make_pair(0.0, 0ul);
//   for (auto sol : solutions) {
//     textMetric = std::make_unique<LevDistTextMetric>();
//     textMetric->setData(filedata, sol.getSource());
//     float textBasedRes = float(textMetric->getMetric());
//     std::cout << textBasedRes << std::endl;

//     textMetric = std::make_unique<JaccardTextMetric>();
//     textMetric->setData(filedata, sol.getSource());
//     textBasedRes = (textBasedRes + float(textMetric->getMetric())) / 2;

//     if (textBasedRes > treshold) {
//       break;
//     }
//     if (maxMatch.first < textBasedRes) {
//       maxMatch.first = textBasedRes;
//       maxMatch.second = sol.getSenderId();
//     }
//   }
//   return maxMatch;
// }

// std::pair<float, size_t> SolutionService::getMaxTokenResMetric(
//     std::vector<Solution>& solutions, std::vector<int>& tokens,
//     float treshold) {
//   std::pair<float, size_t> maxMatch = std::make_pair(0.0, 0ul);
//   for (auto sol : solutions) {
//     tokenMetric = std::make_unique<LivDistTokenMetric>();
//     tokenMetric->setData(tokens, sol.getTokens());
//     float tokenBasedRes = float(tokenMetric->getMetric());
//     std::cout << tokenBasedRes << std::endl;

//     tokenMetric = std::make_unique<WShinglingTokenMetric>();
//     tokenMetric->setData(tokens, sol.getSource());
//     tokenBasedRes = (tokenBasedRes + float(tokenMetric->getMetric())) / 2;

//     if (tokenBasedRes > treshold) {
//       break;
//     }
//     if (maxMatch.first < tokenBasedRes) {
//       maxMatch.first = tokenBasedRes;
//       maxMatch.second = sol.getSenderId();
//     }
//   }
//   return maxMatch;
// }

Solution SolutionService::createSolution(size_t userId, size_t taskId,
                                         const std::string& filename,
                                         const std::string& filedata) {
  try {
    std::pair<std::string, bool> fileExtension =
        FileMethods::checkFileExtension(filename);
    if (!fileExtension.second) {
      throw FileExtensionException("unknown file extension");
    }

    setAntlrWrapper(fileExtension.first, filedata);
    std::vector<int> tokensTypes = antlr->getTokensTypes();
    std::string astTree = antlr->getTreeString();

    std::time_t now =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());


    float treshold = taskRepo->getTaskById(taskId).getTreshhold();


    std::vector<Solution> solutions =
        solutionRepo->getSolutionsByTaskId(taskId);

    // float textBasedRes = getMaxTextResMetric(solutions, filedata, treshold);
    // float tokenBasedRes getMaxTokenResMetric(solutions, tokensTypes,
    // treshold);

    std::string result = setResultVerdict(0, 0, treshold);
    // std::string result = setResultVerdict(textBasedRes, tokenBasedRes,
    // treshold);
    Solution sol =
        Solution(std::ctime(&now), userId, filedata, antlr->getTokensString(),
                 astTree, taskId, result);
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

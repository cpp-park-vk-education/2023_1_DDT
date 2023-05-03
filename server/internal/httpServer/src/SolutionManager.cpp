//
// Created by Николай Степанов on 03.05.2023.
//
#include "SolutionManager.h"

SolutionManager::SolutionManager() {}

Response SolutionManager::getAllSolutions(const Request &req) {
    return Response();
}

Response SolutionManager::createSolution(const Request &req) {
    return Response();
}

Response SolutionManager::getMetrics(const Request &req) {
    return Response();
}

std::string SolutionManager::getParam(const std::string &path, const std::string &name) {
    return std::string();
}

void SolutionManager::setService(std::shared_ptr<ISolutionService> service) {
    solutionService = service;
}

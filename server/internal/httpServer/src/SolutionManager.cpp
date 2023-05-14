//
// Created by Николай Степанов on 03.05.2023.
//
#include "SolutionManager.h"

#include <utility>
#include "TmpSolutionService.h"

SolutionManager::SolutionManager() :
    serializer(std::make_shared<Serializer>()) {};

void SolutionManager::setService(std::shared_ptr<ISolutionService> service) {
    solutionService = std::move(service);
}

http::message_generator SolutionManager::createSolution(http::request<http::string_body>&& req) {
    size_t user_id, task_id;
    std::string source;
    std::tie(user_id, source, task_id) = serializer->deserialNewSolutionData(req.body());
    Solution sol = TmpSolutionService::createSolution(user_id, task_id, source);
//    sol = solutionService->createSolution(user_id, task_id, source);
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/plain");
    res.keep_alive(req.keep_alive());
    res.body() = serializer->serialSolution(sol);
    res.prepare_payload();
    return res;
}

http::message_generator SolutionManager::getAllSolutions(http::request<http::string_body>&& req) {
    size_t user_id, task_id;
    std::tie(user_id, task_id) = serializer->deserialTaskData(req.body());
    std::vector<Solution> solutions;
    solutions = solutionService->getSolutionsByUserAndTaskId(user_id, task_id);
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/plain");
    res.keep_alive(req.keep_alive());
    res.body() = serializer->serialSolutions(solutions);
    res.prepare_payload();
    return res;
}


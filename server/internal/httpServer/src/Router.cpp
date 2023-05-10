#include "Router.h"

#include <iostream>
#include <string>

#include "Utils.h"

http::response<http::string_body> Router::getBadRequest(const http::request<http::string_body>& request,
                                                beast::string_view why) {
    http::response<http::string_body> res{http::status::bad_request, request.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/plain");
    res.keep_alive(request.keep_alive());
    res.body() = std::string(why);
    res.prepare_payload();
    return res;
}

Router::Router(std::string_view doc_root_) :
          solutionManager(std::make_shared<SolutionManager>()),
          userManager(std::make_shared<UserManager>()),
          taskManager(std::make_shared<TaskManager>()),
          doc_root(doc_root_) {}


http::message_generator Router::handleRequest(http::request<http::string_body> &&req) {

    if(req.method() != http::verb::get && req.method() != http::verb::post)
        return getBadRequest(req, "Unknown HTTP-method");

    if(req.target().empty() || req.target()[0] != '/' ||
       req.target().find("..") != beast::string_view::npos) {
        return getBadRequest(req, "Illegal request-target");
    }

    std::cout << req.target() << std::endl;

    if (req.target() == "/solution/submit") {
        return solutionManager->createSolution(std::move(req));
    } else if (req.target() == "/solution/metrics") {
        return solutionManager->getMetrics(std::move(req));
    } else if (req.target() == "/solution/all") {
        return solutionManager->getAllSolutions(std::move(req));
    } else if (req.target() == "/user/register") {
        return userManager->registerUser(std::move(req));
    } else if (req.target() == "/user/login") {
        return userManager->loginUser(std::move(req));
    } else if (req.target() == "/task/create") {
        return taskManager->createTask(std::move(req));
    } else if (req.target() == "/task/all") {
        return taskManager->getAllTasks(std::move(req));
    }

    return getBadRequest(req, "Unknown request-target");
}
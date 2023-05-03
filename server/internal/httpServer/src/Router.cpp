#include "Router.h"

#include <iostream>
#include <string>
#include <utility>

#include "Response.h"

Router::Router() :
          solutionManager(std::make_shared<SolutionManager>()),
          userManager(std::make_shared<UserManager>()) {}

void Router::handleRequest(const Request& req, Response& res) {}

bool Router::decodeUrl(const std::string& in, std::string& out) {}

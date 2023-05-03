#ifndef APP_HTTPSERVER_HTTPSERVER_MANAGERS_ISolutionMANAGER_H_
#define APP_HTTPSERVER_HTTPSERVER_MANAGERS_ISolutionMANAGER_H_

#include <memory>
#include <string>

#include "Response.h"
#include "Request.h"

class ISolutionManager {
public:
    virtual Response getAllSolutions(const Request &req) = 0;
    virtual Response createSolution(const Request &req) = 0;
    virtual Response getMetrics(const Request &req) = 0;
};

#endif  // APP_HTTPSERVER_HTTPSERVER_MANAGERS_ISolutionMANAGER_H_

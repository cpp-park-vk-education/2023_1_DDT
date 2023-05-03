#ifndef APP_HTTPSERVER_HTTPSERVER_MANAGERS_SolutionMANAGER_H_
#define APP_HTTPSERVER_HTTPSERVER_MANAGERS_SolutionMANAGER_H_

#include <memory>
#include <string>

#include "Response.h"
#include "Request.h"
#include "Serializer.h"
#include "ISolutionManager.h"
#include "ISolutionService.h"

class SolutionManager : public ISolutionManager {
 public:
    SolutionManager();
    Response getAllSolutions(const Request &req) override;
    Response createSolution(const Request &req) override;
    Response getMetrics(const Request &req) override;
    void setService(std::shared_ptr<ISolutionService> service);

 private:
    std::shared_ptr<ISolutionService> solutionService;
    std::shared_ptr<Serializer> serializer;
    static std::string getParam(const std::string& path, const std::string& name);
};

#endif  // APP_HTTPSERVER_HTTPSERVER_MANAGERS_SolutionMANAGER_H_

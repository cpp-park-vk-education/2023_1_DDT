#ifndef APP_HTTPSERVER_HTTPSERVER_MANAGERS_TaskMANAGER_H_
#define APP_HTTPSERVER_HTTPSERVER_MANAGERS_TaskMANAGER_H_

#include <memory>
#include <string>

#include "Response.h"
#include "Request.h"
#include "Serializer.h"
#include "ITaskManager.h"
#include "ITaskService.h"

class TaskManager : public ITaskManager {
public:
    TaskManager();
    Response createTask(const Request &req) override;
    Response getAllTasks(const Request &req) override;
    void setService(std::shared_ptr<ITaskService> service);
private:
    std::shared_ptr<ITaskService> taskService;
    std::shared_ptr<Serializer> serializer;
    static std::string getParam(const std::string& path, const std::string& name);
};

#endif  // APP_HTTPSERVER_HTTPSERVER_MANAGERS_TaskMANAGER_H_

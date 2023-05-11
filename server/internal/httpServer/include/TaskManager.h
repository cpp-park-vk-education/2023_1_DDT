#ifndef APP_HTTPSERVER_HTTPSERVER_MANAGERS_TaskMANAGER_H_
#define APP_HTTPSERVER_HTTPSERVER_MANAGERS_TaskMANAGER_H_

#include <memory>
#include <string>

#include "Serializer.h"
#include "ITaskManager.h"
#include "ITaskService.h"

class TaskManager : public ITaskManager {
public:
    TaskManager();
    http::message_generator createTask(http::request<http::string_body>&& req) override;
    http::message_generator getAllTasks(http::request<http::string_body>&& req) override;
    void setService(std::shared_ptr<ITaskService> service);
private:
    std::shared_ptr<ITaskService> taskService;
    std::shared_ptr<Serializer> serializer;
};

#endif  // APP_HTTPSERVER_HTTPSERVER_MANAGERS_TaskMANAGER_H_
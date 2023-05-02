#include "TaskService.h"

TaskService::TaskService(std::unique_ptr<ITaskRepository> taskRepo)
    : taskRepo(std::move(taskRepo)) {}

Task TaskService::createTask(std::string desc) { return Task(); }

std::vector<Task> TaskService::getAllTasks(size_t id) {
  return std::vector<Task>();
}

void TaskService::deleteTask(size_t id) {}

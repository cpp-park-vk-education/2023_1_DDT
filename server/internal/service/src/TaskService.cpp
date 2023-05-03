#include "TaskService.h"

TaskService::TaskService(std::unique_ptr<ITaskRepository> taskRepo)
    : taskRepo(std::move(taskRepo)) {}

Task TaskService::createTask(std::string desc) {
  size_t id = taskRepo->storeTask(Task(desc));
  return Task(id, desc);
}

std::vector<Task> TaskService::getAllTasks() { return std::vector<Task>(); }

Task TaskService::getTask(size_t id) { return taskRepo->getTaskById(id); }

void TaskService::deleteTask(size_t id) { taskRepo->deleteTaskById(id); }

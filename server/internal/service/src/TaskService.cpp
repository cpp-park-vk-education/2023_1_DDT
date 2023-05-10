#include "TaskService.h"

#include "TaskRepository.hpp"

TaskService::TaskService()
    : taskRepo(std::make_unique<TaskRepository>()) {
}

Task TaskService::createTask(std::string desc) {
  size_t id = taskRepo->storeTask(Task(desc));
  return Task(id, desc);
}

std::vector<Task> TaskService::getAllTasks() { return std::vector<Task>(); }

Task TaskService::getTask(size_t id) { return taskRepo->getTaskById(id); }

void TaskService::deleteTask(size_t id) { taskRepo->deleteTaskById(id); }

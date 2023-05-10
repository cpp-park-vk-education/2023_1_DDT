#include "TaskService.h"

TaskService::TaskService(std::unique_ptr<ITaskRepository> taskRepo)
    : taskRepo(std::move(taskRepo)) {}

TaskService::TaskService() {
  // TODO: раскоментировать, когда будет реализация
  // taskRepo = std::make_unique<TaskRepository>();
}    

Task TaskService::createTask(const std::string& desc) {
  try {
    Task task = Task(desc);
    size_t id = taskRepo->storeTask(Task(desc));
    task.setId(id);
    return task;
  } catch (std::exception& e) {
    throw e;
  }
}

std::vector<Task> TaskService::getAllTasks() {
  try {
    return taskRepo->getAllTasks();
  } catch (std::exception& e) {
    throw e;
  }
}

Task TaskService::getTask(size_t id) {
  try {
    return taskRepo->getTaskById(id);
  } catch (std::exception& e) {
    throw e;
  }
}

void TaskService::deleteTask(size_t id) {
  try {
    taskRepo->deleteTaskById(id);
  } catch (std::exception& e) {
    throw e;
  }
}

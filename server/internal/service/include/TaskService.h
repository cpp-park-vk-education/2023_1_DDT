#pragma once

#include <memory>

#include "ITaskRepository.hpp"
#include "ITaskService.h"

class TaskService : public ITaskService {
 private:
  std::unique_ptr<ITaskRepository> taskRepo;

 public:
  TaskService(std::unique_ptr<ITaskRepository> taskRepo);
  ~TaskService() override = default;
  Task createTask(std::string desc) override;
  Task getTask(size_t id) override;
  std::vector<Task> getAllTasks() override;
  void deleteTask(size_t id) override;
};

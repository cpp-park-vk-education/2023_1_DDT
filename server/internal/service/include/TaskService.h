#pragma once

#include <memory>

#include "ITaskRepository.hpp"
#include "ITaskService.h"

class TaskService : ITaskService {
 private:
  std::unique_ptr<ITaskRepository> taskRepo;

 public:
  explicit TaskService(std::unique_ptr<ITaskRepository> taskRepo);
  Task createTask(std::string desc) override;
  std::vector<Task> getAllTasks(size_t id) override;
  void deleteTask(size_t id) override;
};

#pragma once
#include "Task.hpp"
#include <vector>


class ITaskService {
 public:
  virtual Task createTask(std::string desc) = 0;
  virtual std::vector<Task> getAllTasks(size_t id) = 0;
  virtual void deleteTask(size_t id) = 0;
};

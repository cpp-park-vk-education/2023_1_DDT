#pragma once
#include <vector>

#include "Task.hpp"

class ITaskService {
 public:
  virtual ~ITaskService() = default;
  virtual Task createTask(const std::string& desc,float treshold) = 0;
  virtual Task getTask(size_t id) = 0;
  virtual std::vector<Task> getAllTasks() = 0;
  virtual void deleteTask(size_t id) = 0;
};

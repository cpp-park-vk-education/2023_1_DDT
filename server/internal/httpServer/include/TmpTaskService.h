#pragma once

#include <vector>
#include <string>
#include "Task.hpp"

class TmpTaskService {
public:
    static void createTask(std::string description) {
        count++;
        Task task(count, description);
        tasks.push_back(task);
    }

    static std::vector<Task> getAllTasks() {
        return tasks;
    }

    static std::size_t count;
    static std::vector<Task> tasks;
};

std::vector<Task> TmpTaskService::tasks = {Task(1, "1 description                            1\n"
                                                   "\n"
                                                   "\n"
                                                   "\n"
                                                   "\n"
                                                   "\n"
                                                   "\n"
                                                   "\n"
                                                   "\n"
                                                   "\n"
                                                   "\n"
                                                   "\n"
                                                   "\n"
                                                   "\n"
                                                   "14\n"),
                                                  Task(2, "2 description"),
                                                  Task(3, "3 description")};
std::size_t TmpTaskService::count = 3;
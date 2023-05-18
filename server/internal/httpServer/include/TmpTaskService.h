#pragma once

#include <string>
#include <vector>

#include "Task.hpp"

class TmpTaskService {
 public:
    static void createTask(std::string description) {
        count++;
        Task task(count, description, 0.5);
        tasks.push_back(task);
    }

    static std::vector<Task> getAllTasks() { return tasks; }

    static std::size_t count;
    static std::vector<Task> tasks;
};

std::vector<Task> TmpTaskService::tasks = {Task(1,
                                                "1 description                            1\n"
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
                                                "14\n",
                                                0.5),
                                           Task(2, "2 description", 0.5), Task(3, "3 description", 0.5)};
std::size_t TmpTaskService::count = 3;
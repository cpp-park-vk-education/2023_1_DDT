#ifndef SOURCEDOUT_TASK_HPP
#define SOURCEDOUT_TASK_HPP
#include <iostream>
#include <utility>
class Task{
private:
    size_t id;
    std::string description;

public:
    Task(size_t id, std::string description) : id(id), description(std::move(description)) {}
    [[nodiscard]] size_t getId() const {
        return id;
    }

    [[nodiscard]] const std::string &getDescription() const {
        return description;
    }

    void setDescription(const std::string &description_) {
        Task::description = description_;
    }

public:
};
#endif //SOURCEDOUT_TASK_HPP

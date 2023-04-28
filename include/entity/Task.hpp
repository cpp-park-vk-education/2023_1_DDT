#ifndef SOURCEDOUT_TASK_HPP
#define SOURCEDOUT_TASK_HPP
#include <iostream>
class Task{
private:
    size_t id;
    std::string description;
public:
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

#ifndef SOURCEDOUT_TASK_HPP
#define SOURCEDOUT_TASK_HPP
#include <iostream>
#include <utility>
class Task{
private:
    size_t id;
    std::string description;

public:
    Task()=default;
    ~Task() = default;
    Task(size_t id, std::string description);

    explicit Task(std::string description);

    [[nodiscard]] size_t getId() const;

    void setId(size_t id);

    [[nodiscard]] const std::string &getDescription() const;

    void setDescription(const std::string &description);
};
#endif //SOURCEDOUT_TASK_HPP

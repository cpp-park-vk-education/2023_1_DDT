#ifndef SOURCEDOUT_TASK_HPP
#define SOURCEDOUT_TASK_HPP
#include <iostream>
#include <utility>
class Task{
private:
    size_t id;
    std::string description;
    float treshhold;

public:
    Task(size_t id, std::string description_, float  treshold_) noexcept;

    Task(std::string description_, float treshold_) noexcept;

    Task() noexcept;

    [[nodiscard]] size_t getId() const noexcept;

    [[nodiscard]] const std::string &getDescription() const noexcept;

    float getTreshhold() const noexcept;

    void setTreshhold(float treshhold) noexcept;

    void setDescription(const std::string &description) noexcept;

    void setId(size_t id) noexcept;

    bool operator==(const Task &rhs) const noexcept;

    bool operator!=(const Task &rhs) const noexcept;

};
#endif //SOURCEDOUT_TASK_HPP

#include "Task.hpp"
#include <iostream>

Task::Task(std::string description_, float treshold_) noexcept : id(0), description(std::move(description_)),
                                                        treshhold(treshold_) {}

Task::Task(size_t id, std::string description_, float treshold_) noexcept : id(id), description(std::move(description_)),
                                                                   treshhold(treshold_) {}
Task::Task() noexcept:id(0), treshhold(0) {
}

unsigned long Task::getId() const noexcept {
    return id;
}

const std::string &Task::getDescription() const noexcept {
    return description;
}

void Task::setId(size_t id_) noexcept {
    id = id_;
}

void Task::setDescription(const std::string &description_) noexcept {
    Task::description = description_;
}

bool Task::operator==(const Task &rhs) const noexcept {
    return id == rhs.id;
}

bool Task::operator!=(const Task &rhs) const noexcept {
    return !(rhs == *this);
}

float Task::getTreshhold() const noexcept {
    return treshhold;
}

void Task::setTreshhold(float treshhold_) noexcept {
    Task::treshhold = treshhold_;
}


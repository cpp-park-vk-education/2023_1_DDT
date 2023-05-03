#pragma once

#include "../include/Task.hpp"
#include <iostream>
#include <utility>

unsigned long Task::getId() const {
    return id;
}

Task::Task(size_t id, std::string description) : id(id), description(std::move(description)) {}

Task::Task(std::string description) : id(0), description(std::move(description)) {}

const std::string &Task::getDescription() const {
    return description;
}

void Task::setId(size_t id_) {
    id = id_;
}

void Task::setDescription(const std::string &description_) {
    Task::description = description_;
}

bool Task::operator==(const Task &rhs) const {
    return id == rhs.id;
}

bool Task::operator!=(const Task &rhs) const {
    return !(rhs == *this);
}

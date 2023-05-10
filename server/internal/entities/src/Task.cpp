#pragma once

#include "../include/Task.hpp"
#include <iostream>
#include <utility>

unsigned long Task::getId() const {
    return id;
}

void Task::setId(size_t id_) {
    id=id_;
}

Task::Task(size_t id, std::string description) : id(id), description(std::move(description)) {}

Task::Task(std::string description) : id(0), description(std::move(description)) {}

const std::string &Task::getDescription() const {
    return description;
}

void Task::setDescription(const std::string &description_) {
    Task::description = description_;
}

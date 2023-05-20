#pragma once

#include <iostream>

struct Task{
    std::size_t id;
    std::string description;

    Task(std::size_t id, std::string_view desc);
};

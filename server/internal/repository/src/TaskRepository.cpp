#include <iostream>
#include "Task.hpp"
#include <pqxx/pqxx>
#include "TaskRepository.hpp"

std::optional<Task> TaskRepository::getTaskById(size_t id) {
    try {
        auto c = manager->connection();
        std::string sql = "SELECT * FROM tasks WHERE id=" + std::to_string(id);
        nontransaction n(*c);
        result r(n.exec(sql));
        manager->freeConnection(c);
        if (r.empty()) {
            return std::nullopt;
        }
        return makeTask(r.begin());
    } catch (...) {
        throw;
    }
}

void TaskRepository::updateTask(Task task) {
    try {
        auto c = manager->connection();
        std::string sql = (boost::format("UPDATE tasks SET description = '%s', treshold = '%s';") %
                           task.getDescription() % task.getTreshhold()).str();
        work w(*c);
        w.exec(sql);
        manager->freeConnection(c);
    } catch (...) {
        throw;
    }
}

size_t TaskRepository::storeTask(Task task) {
    try {
        auto c = manager->connection();
        std::string sql = (boost::format("INSERT INTO tasks (description, treshold) "  \
            "VALUES ('%s', '%s') RETURNING id; ") % task.getDescription() % task.getTreshhold()).str();
        work w(*c);
        row r = w.exec1(sql);
        w.commit();
        manager->freeConnection(c);
        return r["id"].as<size_t>();
    } catch (...) {
        throw;
    }
}

void TaskRepository::deleteTask(Task task) {
    deleteTaskById(task.getId());
}

void TaskRepository::deleteTaskById(size_t task_id) {
    try {
        auto c = manager->connection();
        std::string sql = "DELETE FROM tasks WHERE id=" + std::to_string(task_id);
        work w(*c);
        w.exec(sql);
        w.commit();
        manager->freeConnection(c);
    } catch (...) {
        throw;
    }
}

Task TaskRepository::makeTask(const result::const_iterator &c) {
    return {c.at(c.column_number("id")).as<size_t>(),
            c.at(c.column_number("description")).as<std::string>(),
            c.at(c.column_number("treshold")).as<float>()};
}

TaskRepository::TaskRepository() {
    manager = std::make_shared<dbManager>();
}

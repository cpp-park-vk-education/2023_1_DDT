
#include <iostream>
#include <fstream>
#include "Task.hpp"
#include <pqxx/pqxx>
#include "TaskRepository.hpp"

Task TaskRepository::getTaskById(size_t id) {
    try {
        auto c = manager->connection();
        std::string sql = "SELECT * FROM tasks WHERE id=" + std::to_string(id);
        nontransaction n(*c);
        result r(n.exec(sql));
        manager->freeConnection(c);
        return makeTask(r.begin());
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

void TaskRepository::updateTask(Task task) {
    try {
        auto c = manager->connection();
        std::string sql = (boost::format("UPDATE tasks SET description = '%s' ;") % task.getDescription()).str();
        work w(*c);
        w.exec(sql);
        manager->freeConnection(c);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

void TaskRepository::storeTask(Task task) {
    try {
        auto c = manager->connection();
        std::string sql = (boost::format("INSERT INTO tasks (description) "  \
            "VALUES ('%s'); ") % task.getDescription()).str();
        work w(*c);
        w.exec(sql);
        w.commit();
        manager->freeConnection(c);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

void TaskRepository::deleteTask(Task task) {
    deleteTaskById(task.getId());
}

void TaskRepository::deleteTaskById(size_t task_id) {
    try {
        auto c = manager->connection();
        work w(*c);
        w.commit();
        manager->freeConnection(c);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

Task TaskRepository::makeTask(const result::const_iterator &c) {
    return {c.at(c.column_number("id")).as<size_t>(),
            c.at(c.column_number("description")).as<std::string>()};
}
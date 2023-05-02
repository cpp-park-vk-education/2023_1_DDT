#pragma once
#include <iostream>
#include <fstream>
#include "Task.hpp"
#include <pqxx/pqxx>
#include "TaskRepository.hpp"

Task TaskRepository::getTaskById(size_t id) {
    try {
        connection c;
        std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
        if (c.is_open()) {
            log << "Opened database successfully: " << c.dbname() << std::endl;
        } else {
            log << "Can't open database" << std::endl;
            std::cerr << "Can't open database" << std::endl;
        }
        std::string sql = "SELECT * FROM tasks WHERE id=" + std::to_string(id);
        nontransaction n(c);
        result r(n.exec(sql));
        log << "OK" << std::endl;
        log.close();
        //c.close();
        return makeTask(r.begin());
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

void TaskRepository::updateTask(Task task) {
    try {
        connection c;
        std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
        if (c.is_open()) {
            log << "Opened database successfully: " << c.dbname() << std::endl;
        } else {
            log << "Can't open database" << std::endl;
            std::cerr << "Can't open database" << std::endl;
        }
        std::string sql = (boost::format("UPDATE tasks SET description = %s ;") % task.getDescription()).str();
        work w(c);
        w.exec(sql);
        log << "OK" << std::endl;
        log.close();
        //c.close();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

void TaskRepository::storeTask(Task task) {
    try {
        connection c;
        std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
        if (c.is_open()) {
            log << "Opened database successfully: " << c.dbname() << std::endl;
        } else {
            log << "Can't open database" << std::endl;
            std::cerr << "Can't open database" << std::endl;
        }
        std::string sql = (boost::format("INSERT INTO tasks (description) "  \
            "VALUES (%s); ") % task.getDescription()).str();
        work w(c);
        w.exec(sql);
        w.commit();
        log << "OK" << std::endl;
        log.close();
        //c.close();
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
        connection c;
        std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
        if (c.is_open()) {
            log << "Opened database successfully: " << c.dbname() << std::endl;
        } else {
            log << "Can't open database" << std::endl;
            std::cerr << "Can't open database" << std::endl;
        }
        std::string sql = "DELETE FROM tasks WHERE id=" + std::to_string(task_id);
        work w(c);
        w.commit();
        log << "OK" << std::endl;
        log.close();
        //c.close();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

Task TaskRepository::makeTask(const result::const_iterator &c) {
    return {c.at(c.column_number("id")).as<size_t>(),
            c.at(c.column_number("description")).as<std::string>()};
}
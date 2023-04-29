#ifndef SOURCEDOUT_SOLUTIONREPOSITORY_HPP
#define SOURCEDOUT_SOLUTIONREPOSITORY_HPP

#include <iostream>
#include <pqxx/pqxx>
#include <boost/format.hpp>
#include "ISolutionRepository.hpp"
#include "../entity/Solution.hpp"
#include "../dataBase/conn.hpp"
using namespace pqxx;

class SolutionRepository : ISolutionRepository {
    Solution getSolutionById(size_t id) override {
        try {
            connection c(conn.getData());
            std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
            if (c.is_open()) {
                log << "Opened database successfully: " << c.dbname() << std::endl;
            } else {
                log << "Can't open database" << std::endl;
                std::cerr << "Can't open database" << std::endl;
            }
            std::string sql = "SELECT * FROM Users WHERE id=" + std::to_string(id);
            nontransaction n(c);
            result r(n.exec(sql));
            log << "OK" << std::endl;
            log.close();
            c.close();
            return makeSolution(r.begin());
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            throw e;
        }
    }

    std::vector<Solution> getSolutionsBySenderId(size_t sender_id) override {
        try {
            connection c(conn.getData());
            std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
            if (c.is_open()) {
                log << "Opened database successfully: " << c.dbname() << std::endl;
            } else {
                log << "Can't open database" << std::endl;
                std::cerr << "Can't open database" << std::endl;
            }
            std::string sql = "SELECT * FROM solutions WHERE sender_id=" + std::to_string(sender_id);
            nontransaction n(c);
            result r(n.exec(sql));
            log << "OK" << std::endl;
            log.close();
            c.close();
            std::vector<Solution> solutions;
            for(result::const_iterator k = r.begin(); k != r.end(); ++k)
                solutions.push_back(makeSolution(k));
            return solutions;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            throw e;
        }
    }

    std::vector<Solution> getSolutionsByTaskId(size_t task_id) override {
        try {
            connection c(conn.getData());
            std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
            if (c.is_open()) {
                log << "Opened database successfully: " << c.dbname() << std::endl;
            } else {
                log << "Can't open database" << std::endl;
                std::cerr << "Can't open database" << std::endl;
            }
            std::string sql = "SELECT * FROM solutions WHERE task_id=" + std::to_string(task_id);
            nontransaction n(c);
            result r(n.exec(sql));
            log << "OK" << std::endl;
            log.close();
            c.close();
            std::vector<Solution> solutions;
            for(result::const_iterator k = r.begin(); k != r.end(); ++k)
                solutions.push_back(makeSolution(k));
            return solutions;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            throw e;
        }
    }

    void storeSolution(Solution solution) override {
        try {
            connection c(conn.getData());
            std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
            if (c.is_open()) {
                log << "Opened database successfully: " << c.dbname() << std::endl;
            } else {
                log << "Can't open database" << std::endl;
                std::cerr << "Can't open database" << std::endl;
            }
            std::string sql = (boost::format("INSERT INTO solutions (send_date,sender_id, source, task_id, result) "  \
            "VALUES (%s, %s, %s, %s, %s); ") % solution.getSendDate() % solution.getSenderId() % solution.getSource() % solution.getTaskId() % solution.getResult()).str();
            work w(c);
            w.exec(sql);
            w.commit();
            log << "OK" << std::endl;
            log.close();
            c.close();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            throw e;
        }
    }

    void updateSolution(Solution solution) override {
        try {
            connection c(conn.getData());
            std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
            if (c.is_open()) {
                log << "Opened database successfully: " << c.dbname() << std::endl;
            } else {
                log << "Can't open database" << std::endl;
                std::cerr << "Can't open database" << std::endl;
            }
            std::string sql = (boost::format("UPDATE solutions SET send_date = %s, sender_id = %s, source = %s, task_id = %s, resulr = %s ;")
                    % solution.getSendDate() % solution.getSenderId() % solution.getSource() % solution.getTaskId() % solution.getResult()).str();
            work w(c);
            w.exec(sql);
            log << "OK" << std::endl;
            log.close();
            c.close();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            throw e;
        }
    }

    void deleteSolutionById(size_t id) override {
        try {
            connection c(conn.getData());
            std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
            if (c.is_open()) {
                log << "Opened database successfully: " << c.dbname() << std::endl;
            } else {
                log << "Can't open database" << std::endl;
                std::cerr << "Can't open database" << std::endl;
            }
            std::string sql = "DELETE FROM solutions WHERE id=" + std::to_string(id);
            work w(c);
            w.commit();
            log << "OK" << std::endl;
            log.close();
            c.close();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            throw e;
        }
    }

    void deleteSolution(Solution solution) override {
        deleteSolutionById(solution.getId());
    }

private:
    conn conn;
    static Solution makeSolution(const result::const_iterator& c){
        return {c.at(c.column_number("id")).as<size_t>(),
                c.at(c.column_number("send_date")).as<std::string>(),
                c.at(c.column_number("sender_id")).as<size_t>(),
                c.at(c.column_number("source")).as<std::string>(),
                c.at(c.column_number("task_id")).as<size_t>(),
                c.at(c.column_number("result")).as<std::string>()};
    }
};

#endif //SOURCEDOUT_SOLUTIONREPOSITORY_HPP

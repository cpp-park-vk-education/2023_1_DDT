#include <iostream>
#include <pqxx/pqxx>
#include <boost/format.hpp>
#include "Solution.hpp"
#include "SolutionRepository.hpp"
using namespace pqxx;

std::vector<Solution> SolutionRepository::getSolutions(size_t sender_id, size_t task_id){
    return std::vector<Solution>();
}

Solution SolutionRepository::getSolutionById(size_t id)  {
    try {
        auto c = manager->connection();
        std::string sql = "SELECT * FROM Users WHERE id=" + std::to_string(id);
        nontransaction n(*c);
        result r(n.exec(sql));
        manager->freeConnection(c);
        return makeSolution(r.begin());
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

std::vector<Solution> SolutionRepository::getSolutionsBySenderId(size_t sender_id)  {
    try {
        auto c = manager->connection();
        std::string sql = "SELECT * FROM solutions WHERE sender_id=" + std::to_string(sender_id);
        nontransaction n(*c);
        result r(n.exec(sql));
        std::vector<Solution> solutions;
        manager->freeConnection(c);
        for(result::const_iterator k = r.begin(); k != r.end(); ++k)
            solutions.push_back(makeSolution(k));
        return solutions;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

std::vector<Solution> SolutionRepository::getSolutionsByTaskId(size_t task_id)  {
    try {
        auto c = manager->connection();
        std::string sql = "SELECT * FROM solutions WHERE task_id=" + std::to_string(task_id);
        nontransaction n(*c);
        result r(n.exec(sql));
        std::vector<Solution> solutions;
        manager->freeConnection(c);
        for(result::const_iterator k = r.begin(); k != r.end(); ++k)
            solutions.push_back(makeSolution(k));
        return solutions;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

size_t SolutionRepository::storeSolution(Solution solution)  {
    try {
        auto c = manager->connection();

        std::string sql = (boost::format("INSERT INTO solutions (send_date,sender_id, source, task_id, result, tokens, astTree) "  \
            "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s'); ") % solution.getSendDate() % solution.getSenderId() % solution.getSource() % solution.getTaskId() % solution.getResult() % solution.getTokens() % solution.getAstTree()).str();
        work w(*c);
        w.exec(sql);
        w.commit();
        manager->freeConnection(c);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

void SolutionRepository::updateSolution(Solution solution)  {
    try {
        auto c = manager->connection();

        std::string sql = (boost::format("UPDATE solutions SET send_date = '%s', sender_id = '%s', source = '%s', task_id = '%s', result = '%s', tokens = '%s', astTree = '%s';")
                           % solution.getSendDate() % solution.getSenderId() % solution.getSource() % solution.getTaskId() % solution.getResult() % solution.getTokens() % solution.getAstTree()).str();
        work w(*c);
        w.exec(sql);
        manager->freeConnection(c);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

void SolutionRepository::deleteSolutionById(size_t id)  {
    try {
        auto c = manager->connection();
        std::string sql = "DELETE FROM solutions WHERE id=" + std::to_string(id);
        work w(*c);
        w.commit();
        manager->freeConnection(c);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

void SolutionRepository::deleteSolution(Solution solution)  {
    deleteSolutionById(solution.getId());
}


Solution SolutionRepository::makeSolution(const result::const_iterator& c){
    return {c.at(c.column_number("id")).as<size_t>(),
            c.at(c.column_number("send_date")).as<std::string>(),
            c.at(c.column_number("sender_id")).as<size_t>(),
            c.at(c.column_number("source")).as<std::string>(),
            c.at(c.column_number("tokens")).as<std::string>(),
            c.at(c.column_number("astTree")).as<std::string>(),
            c.at(c.column_number("task_id")).as<size_t>(),
            c.at(c.column_number("result")).as<std::string>()};
}
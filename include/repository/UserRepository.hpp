#ifndef SOURCEDOUT_USERREPOSITORY_HPP
#define SOURCEDOUT_USERREPOSITORY_HPP

#include <iostream>
#include "IUserRepository.hpp"
#include "../entity/User.hpp"
#include "../dataBase/conn.hpp"
#include <pqxx/pqxx>
#include <boost/format.hpp>

using namespace pqxx;

class UserRepository : IUserRepository {
public:
    explicit UserRepository(conn conn_) {
        conn = std::move(conn_);
    }

    User getUserById(size_t id) override {
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
            return makeUser(r.begin());
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            throw e;
        }
    }

    User getUserByLogin(std::string login) override {
        try {
            connection c(conn.getData());
            std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
            if (c.is_open()) {
                log << "Opened database successfully: " << c.dbname() << std::endl;
            } else {
                log << "Can't open database" << std::endl;
                std::cerr << "Can't open database" << std::endl;
            }
            std::string sql = "SELECT * FROM Users WHERE login=" + login;
            nontransaction n(c);
            result r(n.exec(sql));
            log << "OK" << std::endl;
            log.close();
            c.close();
            return makeUser(r.begin());
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            throw e;
        }
    }

    size_t makeUser(User user) override {
        try {
            connection c(conn.getData());
            std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
            if (c.is_open()) {
                log << "Opened database successfully: " << c.dbname() << std::endl;
            } else {
                log << "Can't open database" << std::endl;
                std::cerr << "Can't open database" << std::endl;
            }
            std::string sql = (boost::format("INSERT INTO Users (login,password,username) "  \
            "VALUES (%s, %s, %s); ") % user.getLogin() % user.getPassword() % user.getUsername()).str();
            work w(c);
            w.exec(sql);
            w.commit();
            log << "OK" << std::endl;
            log.close();
            c.close();
            return getUserByLogin(user.getLogin()).getId();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            throw e;
        }
    }

    void deleteUser(User user) override {
        deleteByUserId(user.getId());
    }

    void deleteByUserId(size_t user_id) override {
        try {
            connection c(conn.getData());
            std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
            if (c.is_open()) {
                log << "Opened database successfully: " << c.dbname() << std::endl;
            } else {
                log << "Can't open database" << std::endl;
                std::cerr << "Can't open database" << std::endl;
            }
            std::string sql = "DELETE FROM Users WHERE id=" + std::to_string(user_id);
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

    std::vector<User> getAllUsers() override {
        try {
            connection c(conn.getData());
            std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
            if (c.is_open()) {
                log << "Opened database successfully: " << c.dbname() << std::endl;
            } else {
                log << "Can't open database" << std::endl;
                std::cerr << "Can't open database" << std::endl;
            }
            std::string sql = "SELECT * FROM Users";
            nontransaction n(c);
            result r(n.exec(sql));
            log << "OK" << std::endl;
            log.close();
            c.close();
            std::vector<User> users;
            for(result::const_iterator k = r.begin(); k != r.end(); ++k)
                users.push_back(makeUser(k));
            return users;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            throw e;
        }
    }

    void getUsersByTaskId(size_t id) override {

    }

private:
    static User makeUser(const result::const_iterator& c) {
        return {c.at(c.column_number("id")).as<size_t>(),
                c.at(c.column_number("login")).as<std::string>(),
                c.at(c.column_number("password")).as<std::string>(),
                c.at(c.column_number("username")).as<std::string>()};
    }

    static conn conn;
};

#endif //SOURCEDOUT_USERREPOSITORY_HPP

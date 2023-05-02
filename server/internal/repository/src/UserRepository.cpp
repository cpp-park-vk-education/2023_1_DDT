#pragma once

#include <iostream>
#include <fstream>
#include "User.hpp"
#include "UserRepository.hpp"
#include <pqxx/pqxx>
#include <utility>

User UserRepository::getUserById(size_t id) {
    try {
        connection c(conn_.getData());
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
        //c.close();
        return makeUser(r.begin());
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

User UserRepository::getUserByLogin(std::string login) {
    try {
        connection c(conn_.getData());
        std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
        if (c.is_open()) {
            log << "Opened database successfully: " << c.dbname() << std::endl;
        } else {
            log << "Can't open database" << std::endl;
            std::cerr << "Can't open database" << std::endl;
        }
        std::string sql = (boost::format("SELECT * FROM Users WHERE login= '%s'")% login).str();
        nontransaction n(c);
        result r(n.exec(sql));
        log << "OK" << std::endl;
        log.close();
        //c.close();
        return makeUser(r.begin());
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

size_t UserRepository::makeUser(User user) {
    try {
        connection c(conn_.getData());
        std::ofstream log("log.txt", std::ios_base::out | std::ios_base::app);
        if (c.is_open()) {
            log << "Opened database successfully: " << c.dbname() << std::endl;
        } else {
            log << "Can't open database" << std::endl;
            std::cerr << "Can't open database" << std::endl;
        }
        std::string sql = (boost::format("INSERT INTO users (login,password,username) "  \
            "VALUES ('%s', '%s', '%s'); ") % user.getLogin() % user.getPassword() % user.getUsername()).str();
        work w(c);
        w.exec(sql);
        w.commit();
        log << "OK" << std::endl;
        log.close();

        //c.close();

        return getUserByLogin(user.getLogin()).getId();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

void UserRepository::deleteByUserId(size_t user_id) {
    try {
        connection c;
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
        //c.close();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}


void UserRepository::deleteUser(User user) {
    deleteByUserId(user.getId());
}

std::vector<User> UserRepository::getAllUsers() {
    try {
        connection c;
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
        //c.close();
        std::vector<User> users;
        for (result::const_iterator k = r.begin(); k != r.end(); ++k)
            users.push_back(makeUser(k));
        return users;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

User UserRepository::makeUser(const result::const_iterator &c) {
    return {c.at(c.column_number("id")).as<size_t>(),
            c.at(c.column_number("login")).as<std::string>(),
            c.at(c.column_number("password")).as<std::string>(),
            c.at(c.column_number("username")).as<std::string>()};
}

UserRepository::UserRepository(conn connect) {
    conn_ = std::move(connect);
}

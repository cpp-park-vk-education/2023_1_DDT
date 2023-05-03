
#include <iostream>
#include "User.hpp"
#include "UserRepository.hpp"
#include "dbManager.hpp"
#include <pqxx/pqxx>

std::optional<User> UserRepository::getUserById(size_t id) {
    try {
        auto c = manager->connection();
        std::string sql = "SELECT * FROM Users WHERE id=" + std::to_string(id);
        nontransaction n(*c);
        result r(n.exec(sql));
        manager->freeConnection(c);
        if (r.empty())
            return std::nullopt;
        return makeUser(r.begin());
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

std::optional<User> UserRepository::getUserByLogin(std::string login) {
    try {
        auto c = manager->connection();
        std::string sql = (boost::format("SELECT * FROM Users WHERE login= '%s'") % login).str();
        nontransaction n(*c);
        result r(n.exec(sql));
        manager->freeConnection(c);
        if(r.empty())
            return std::nullopt;
        return makeUser(r.begin());
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

size_t UserRepository::makeUser(User user) {
    try {
        auto c = manager->connection();

        std::string sql = (boost::format("INSERT INTO users (login,password,username) "  \
            "VALUES ('%s', '%s', '%s') RETURNING id; ") % user.getLogin() % user.getPassword() %
                           user.getUsername()).str();
        work w(*c);
        row r = w.exec1(sql);
        w.commit();
        manager->freeConnection(c);
        return r["id"].as<size_t>();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

void UserRepository::deleteByUserId(size_t user_id) {
    try {
        auto c = manager->connection();
        std::string sql = "DELETE FROM Users WHERE id=" + std::to_string(user_id);
        work w(*c);
        w.exec(sql);
        w.commit();
        manager->freeConnection(c);
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
        auto c = manager->connection();
        std::string sql = "SELECT * FROM Users";
        nontransaction n(*c);
        result r(n.exec(sql));
        manager->freeConnection(c);
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

UserRepository::UserRepository() {
    manager = std::make_shared<dbManager>();
}

void UserRepository::update(User user) {
    try {
        auto c = manager->connection();

        std::string sql = (boost::format(
                "UPDATE Users SET login = '%s', password = '%s', username = '%s';")
                           % user.getLogin() % user.getPassword() % user.getUsername()).str();
        work w(*c);
        w.exec(sql);
        manager->freeConnection(c);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

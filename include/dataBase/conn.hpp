#ifndef SOURCEDOUT_CONN_HPP
#define SOURCEDOUT_CONN_HPP

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

struct conn {
    std::string dbname;
    std::string user;
    std::string password;
    std::string hostaddr;
    std::string port;

    conn() {
        std::ifstream f("config.json");
        json data = json::parse(f);
        data.at("dbname").get_to(dbname);
        data.at("user").get_to(user);
        data.at("password").get_to(password);
        data.at("hostaddr").get_to(hostaddr);
        data.at("port").get_to(port);
    }

    [[nodiscard]] std::string getData() const {
        return "dbname = " + dbname + " user = " + user + " password = " + password +
               " hostaddr = " + hostaddr + " port = " + port;
    }
};

#endif //SOURCEDOUT_CONN_HPP

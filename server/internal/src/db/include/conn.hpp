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

    conn();

    [[nodiscard]] std::string getData() const;
};

#endif //SOURCEDOUT_CONN_HPP

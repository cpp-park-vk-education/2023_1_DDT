#pragma once

#include <iostream>
#include "conn.hpp"
#include <fstream>
conn::conn() {
    std::ifstream f("../config.json");
    json data = json::parse(R"(
{
  "dbname": "mydb",
  "user": "postgres",
  "password": "root",
  "hostaddr": "172.28.224.1",
  "port": "5432"
}
)");
    data.at("dbname").get_to(dbname);
    data.at("user").get_to(user);
    data.at("password").get_to(password);
    data.at("hostaddr").get_to(hostaddr);
    data.at("port").get_to(port);
}

std::string conn::getData() const {
    return "dbname = " + dbname + " user = " + user + " password = " + password +
           " hostaddr = " + hostaddr + " port = " + port;
}
//
// Created by qwert on 01.05.2023.
//

#include <pqxx/pqxx>
#include "../include/dbConnection.hpp"

dbConnection::dbConnection() {
    establish_connection();
}

std::shared_ptr<pqxx::connection> dbConnection::connection() const {
    return m_connection;
}

void dbConnection::establish_connection() {
    pqxx::connection c("dbname =mydb" "user = postgres password =root hostaddr =127.0.0.0 port = 5432");
    m_connection.reset(&c);

}

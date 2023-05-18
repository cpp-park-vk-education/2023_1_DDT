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

// void dbConnection::establish_connection() {
//     pqxx::connection c("dbname =mydb" "user = temp password =temp hostaddr =db port = 5432");
//     m_connection.reset(&c);

// }

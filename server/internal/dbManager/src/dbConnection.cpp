//
// Created by qwert on 01.05.2023.
//

#include "../include/dbConnection.hpp"

#include <pqxx/pqxx>

dbConnection::dbConnection() { establish_connection(); }

std::shared_ptr<pqxx::connection> dbConnection::connection() const { return m_connection; }

// void dbConnection::establish_connection() {
//     pqxx::connection c("dbname =mydb" "user = temp password =temp hostaddr =db port = 5432");
//     m_connection.reset(&c);

// }

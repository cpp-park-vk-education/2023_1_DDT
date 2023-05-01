
#ifndef SOURCEDOUT_DBCONNECTION_HPP
#define SOURCEDOUT_DBCONNECTION_HPP

#include <pqxx/connection.hxx>
//#include "dotenv.h"
//using namespace dotenv;
class dbConnection {
public:
    dbConnection();
    [[nodiscard]] std::shared_ptr<pqxx::connection> connection() const;
private:
    void establish_connection();

    std::string m_dbhost = "localhost";
    int         m_dbport = 5432;
    std::string m_dbname = "demo";
    std::string m_dbuser = "postgres";
    std::string m_dbpass = "postgres";

    std::shared_ptr<pqxx::connection>  m_connection;

};


#endif //SOURCEDOUT_DBCONNECTION_HPP

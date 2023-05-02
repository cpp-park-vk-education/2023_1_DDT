#ifndef SOURCEDOUT_DBMANAGER_HPP
#define SOURCEDOUT_DBMANAGER_HPP

#include <pqxx/pqxx>
#include <stack>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <condition_variable>
//#include "dotenv.h"
//using namespace dotenv;
class dbManager {
public:
    dbManager();
    std::shared_ptr<pqxx::connection> connection();
    void freeConnection(const std::shared_ptr<pqxx::connection>&);
private:
    const int POOL_SIZE = 10;
    std::condition_variable m_condition;
    void createPool();
    std::queue<std::shared_ptr<pqxx::connection>> connection_pool;
    std::mutex m_mutex;
};


#endif //SOURCEDOUT_DBMANAGER_HPP

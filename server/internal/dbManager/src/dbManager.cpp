
#include "dbManager.hpp"


dbManager::dbManager() {
    createPool();
}

void dbManager::createPool() {
    std::lock_guard<std::mutex> locker_(m_mutex);

    for (auto i = 0; i < POOL_SIZE; i++) {
        connection_pool.emplace(std::make_shared<pqxx::connection>(
                "dbname =mydb user = postgres password =root hostaddr =172.28.224.1 port = 5432"));
    }
}

std::shared_ptr<pqxx::connection> dbManager::connection() {
    std::unique_lock<std::mutex> lock_(m_mutex);

    // if pool is empty, then wait until it notifies back
    while (connection_pool.empty()) {
        m_condition.wait(lock_);
    }

    // get new connection in queue
    auto conn_ = connection_pool.front();
    // immediately pop as we will use it now
    connection_pool.pop();

    return conn_;
}

void dbManager::freeConnection(const std::shared_ptr<pqxx::connection> &conn_) {
    std::unique_lock<std::mutex> lock_(m_mutex);

    // push a new connection into a pool
    connection_pool.push(conn_);

    // unlock mutex
    lock_.unlock();

    // notify one of thread that is waiting
    m_condition.notify_one();
}

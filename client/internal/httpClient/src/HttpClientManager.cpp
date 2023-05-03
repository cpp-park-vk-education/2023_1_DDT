#include "httpClientManager.h"

#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <memory>

HttpClientManager::HttpClientManager(const std::string &domain,
                                     const std::string &ip,
                                     const unsigned short &port,
                                     std::string saved_path_)
                : host(domain, ip, port), client(), serializer(), saved_path(std::move(saved_path_)) {}

unsigned int HttpClientManager::loginUser(const std::string &login, const std::string &password) {
    return 0;
}

unsigned int HttpClientManager::registerUser(const std::string &login, const std::string &username,
                                             const std::string &password) {
    return 0;
}

unsigned int HttpClientManager::submitSolution(const int &user_id, const std::string &path_to_sound) {
    return 0;
}

unsigned int HttpClientManager::getAllSolutionsForTask(const int &user_id, const int &task_id) {
    return 0;
}

std::vector<Metric> HttpClientManager::getMetrics(const int &sol_id) {
    return std::vector<Metric>();
}

void HttpClientManager::setHttpClient(std::shared_ptr<IHttpClient> client_) {
    client = client_;
}

std::vector<Task> HttpClientManager::getAllTasks() {
    return std::vector<Task>();
}

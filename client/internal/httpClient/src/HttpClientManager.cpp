#include "HttpClientManager.h"

#include <vector>
#include <string>
#include <memory>

#include "HttpClient.h"

HttpClientManager::HttpClientManager(std::string_view host_, std::string_view port_, std::string_view saved_path_) :
        host(host_), port(port_), saved_path(saved_path_),
        client(std::make_shared<HttpClient>(host_, port_)),
        serializer(std::make_shared<Serializer>()) {}

unsigned int HttpClientManager::loginUser(const std::string &login, const std::string &password) {

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

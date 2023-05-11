#include "HttpClientManager.h"

#include <vector>
#include <string>
#include <memory>

#include "HttpClient.h"

HttpClientManager::HttpClientManager(std::string_view host_, std::string_view port_) :
        host(host_), port(port_),
        client(std::make_shared<HttpClient>(host_, port_)),
        serializer(std::make_shared<Serializer>()) {}

std::pair<unsigned, User> HttpClientManager::loginUser(const std::string &login, const std::string &password) {
    std::string body = serializer->serialLoginData(login, password);
    http::response<http::dynamic_body> res = client->makeGetRequest("/user/login", body);
    unsigned status = res.result_int();
    std::string res_body;
    for (auto seq : res.body().data()) {
        auto* cbuf = boost::asio::buffer_cast<const char*>(seq);
        res_body.append(cbuf, boost::asio::buffer_size(seq));
    }
    User user = serializer->deserialUserData(res_body);
    return {status, user};
}

std::pair<unsigned, User> HttpClientManager::registerUser(const std::string &login, const std::string &username,
                                             const std::string &password) {
    std::string body = serializer->serialRegisterData(login, username, password);
    http::response<http::dynamic_body> res = client->makeGetRequest("/user/register", body);
    unsigned status = res.result_int();
    std::string res_body;
    for (auto seq : res.body().data()) {
        auto* cbuf = boost::asio::buffer_cast<const char*>(seq);
        res_body.append(cbuf, boost::asio::buffer_size(seq));
    }
    User user = serializer->deserialUserData(res_body);
    return {status, user};
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

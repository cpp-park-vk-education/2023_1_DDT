#ifndef APP_HTTPCLIENT_HTTPCLIENTMANAGER_HTTPCLIENTMANAGER_H_
#define APP_HTTPCLIENT_HTTPCLIENTMANAGER_HTTPCLIENTMANAGER_H_

#include <string>
#include <vector>
#include <utility>

#include "IHttpClient.h"
#include "User.h"
#include "Solution.h"
#include "Task.h"
#include "Metric.h"

class HttpClientManager {
 public:
    HttpClientManager(const std::string &domain, const std::string &ip, const unsigned short &port,
                      std::string saved_path_);
    unsigned int loginUser(const std::string &login, const std::string &password);
    unsigned int registerUser(const std::string &login, const std::string &username, const std::string &password);
    unsigned int submitSolution(const int& user_id, const std::string &path_to_sound);
    unsigned int getAllSolutionsForTask(const int& user_id, const int& task_id);
    std::vector<Task> getAllTasks();
    std::vector<Metric> getMetrics(const int& sol_id);
    void setHttpClient(std::shared_ptr<IHttpClient> client_);
 private:
    std::string saved_path;
    Host host;
    std::shared_ptr<IHttpClient> client;
    Serializer serializer;
};


#endif  // APP_HTTPCLIENT_HTTPCLIENTMANAGER_HTTPCLIENTMANAGER_H_

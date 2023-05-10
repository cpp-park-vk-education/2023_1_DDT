#ifndef APP_HTTPSERVER_HTTPSERVER_MANAGERS_SERIALIZER_H_
#define APP_HTTPSERVER_HTTPSERVER_MANAGERS_SERIALIZER_H_

#include <vector>
#include <utility>
#include <string>

#include "Solution.hpp"
#include "User.hpp"
#include "Task.hpp"

class Serializer {
public:
    std::tuple<std::size_t, std::string, std::size_t> deserialNewSolutionData(const std::string& val);
    std::tuple<std::size_t, std::size_t> deserialTaskData(const std::string &val);
    std::string deserialNewTaskData(const std::string &val);
    size_t deserialSolutionData(const std::string& val);
    std::tuple<std::string, std::string> deserialUserData(const std::string& val);
    std::tuple<std::string, std::string, std::string> deserialNewUserData(const std::string &val);

    std::string serialSolutions(const std::vector<Solution>& solutions);
    std::string serialAllTasks(const std::vector<Task>& tasks);
};


#endif  // APP_HTTPSERVER_HTTPSERVER_MANAGERS_SERIALIZER_H_

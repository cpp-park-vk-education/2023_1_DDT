#include "Serializer.h"

#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

std::tuple<std::size_t, std::size_t, std::string, std::string>
Serializer::deserialNewSolutionData(const std::string &val) {
    std::stringstream ss;
    ss << val;
    boost::property_tree::ptree json;
    boost::property_tree::read_json(ss, json);
    std::tuple<std::size_t, std::size_t, std::string, std::string> res = {
        json.get<std::size_t>("user_id"),
        json.get<std::size_t>("task_id"),
        json.get<std::string>("filename"),
        json.get<std::string>("filedata")
    };
    return res;
}

size_t Serializer::deserialSolutionData(const std::string &val) {
    std::stringstream ss;
    ss << val;
    boost::property_tree::ptree json;
    boost::property_tree::read_json(ss, json);
    return json.get<std::size_t>("sol_id");
}

std::tuple<std::size_t, std::size_t> Serializer::deserialTaskData(const std::string &val) {
    std::stringstream ss;
    ss << val;
    boost::property_tree::ptree json;
    boost::property_tree::read_json(ss, json);
    std::tuple<std::size_t, std::size_t> res = {
            json.get<std::size_t>("user_id"),
            json.get<std::size_t>("task_id")
    };
    return res;
}

std::string Serializer::deserialNewTaskData(const std::string &val) {
    std::stringstream ss;
    ss << val;
    boost::property_tree::ptree json;
    boost::property_tree::read_json(ss, json);
    return json.get<std::string>("description");
}

std::tuple<std::string, std::string> Serializer::deserialUserData(const std::string &val) {
    std::stringstream ss;
    ss << val;
    boost::property_tree::ptree json;
    boost::property_tree::read_json(ss, json);
    std::tuple<std::string, std::string> res = {
            json.get<std::string>("login"),
            json.get<std::string>("password")
    };
    return res;
}

std::tuple<std::string, std::string, std::string> Serializer::deserialNewUserData(const std::string &val) {
    std::stringstream ss;
    ss << val;
    boost::property_tree::ptree json;
    boost::property_tree::read_json(ss, json);
    std::tuple<std::string, std::string, std::string> res = {
            json.get<std::string>("login"),
            json.get<std::string>("password"),
            json.get<std::string>("username")
    };
    return res;
}

std::string Serializer::serialSolutions(const std::vector<Solution> &solutions) {
    boost::property_tree::ptree json;
    json.put("count", solutions.size());
    boost::property_tree::ptree solutions_nodes;
    for (auto &i : solutions) {
        boost::property_tree::ptree node;
        node.put("sol_id", i.getId());
        node.put("task_id", i.getTaskId());
        solutions_nodes.push_back(std::make_pair("", node));
    }
    json.add_child("solutions", solutions_nodes);
    std::stringstream out;
    boost::property_tree::write_json(out, json);
    return out.str();
}

std::string Serializer::serialAllTasks(const std::vector<Task> &tasks) {
    boost::property_tree::ptree json;
    json.put("count", tasks.size());
    boost::property_tree::ptree tasks_nodes;
    for (auto &i : tasks) {
        boost::property_tree::ptree node;
        node.put("task_id", i.getId());
        node.put("description", i.getDescription());
        tasks_nodes.push_back(std::make_pair("", node));
    }
    json.add_child("tasks", tasks_nodes);
    std::stringstream out;
    boost::property_tree::write_json(out, json);
    return out.str();
}

std::string Serializer::serialUserData(const User &user) {
    boost::property_tree::ptree json;
    json.put("user_id", user.getId());
    json.put("login", user.getLogin());
    json.put("username", user.getUsername());
    json.put("password", user.getPassword());
    std::stringstream out;
    boost::property_tree::write_json(out, json);
    return out.str();
}

std::string Serializer::serialSolution(const Solution &sol) {
    boost::property_tree::ptree json;
    json.put("sol_id", sol.getId());
    json.put("source", sol.getSource());
    json.put("result", sol.getResult());
    std::stringstream out;
    boost::property_tree::write_json(out, json);
    return out.str();
}

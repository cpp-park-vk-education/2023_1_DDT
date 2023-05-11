#include "Serializer.h"

#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

std::string Serializer::serialLoginData(std::string_view login, std::string_view password) {
    boost::property_tree::ptree json;
    json.put("login", login);
    json.put("password", password);
    std::stringstream out;
    boost::property_tree::write_json(out, json);
    return out.str();
}

User Serializer::deserialUserData(std::string_view body) {
    std::stringstream ss;
    ss << body;
    boost::property_tree::ptree json;
    boost::property_tree::read_json(ss, json);
    User res = {
            json.get<std::size_t>("user_id"),
            json.get<std::string>("login"),
            json.get<std::string>("password"),
            json.get<std::string>("username")
    };
    return res;
}

std::string
Serializer::serialRegisterData(std::string_view login, std::string_view username, std::string_view password) {
    boost::property_tree::ptree json;
    json.put("login", login);
    json.put("username", username);
    json.put("password", password);
    std::stringstream out;
    boost::property_tree::write_json(out, json);
    return out.str();
}

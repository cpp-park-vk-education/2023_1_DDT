//
// Created by Николай Степанов on 11.05.2023.
//
#include "Core.h"
#include "HttpClientManager.h"

const std::string CLIENT_IP = "0.0.0.0";
const std::string CLIENT_PORT = "80";
HttpClientManager client(CLIENT_IP, CLIENT_PORT);

unsigned Core::signUp(const std::string &login, const std::string &username, const std::string &pass) {
    auto res = client.registerUser(login, username, pass);
    user_id = res.second.id;
    return res.first;
}

unsigned Core::login(const std::string &login, const std::string &pass) {
    auto res = client.loginUser(login, pass);
    user_id = res.second.id;
    return res.first;
}

void Core::logout() {
    user_id = -1;
}


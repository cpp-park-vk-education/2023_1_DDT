//
// Created by Николай Степанов on 11.05.2023.
//
#include "Core.h"
#include "HttpClientManager.h"

const std::string CLIENT_IP = "0.0.0.0";
const std::string CLIENT_PORT = "8080";
HttpClientManager client(CLIENT_IP, CLIENT_PORT);

std::size_t Core::user_id = -1;

unsigned Core::signUp(const std::string &login, const std::string &username, const std::string &pass) {
    auto res = client.registerUser(login, username, pass);
    Core::user_id = res.second.id;
    return res.first;
}

unsigned Core::login(const std::string &login, const std::string &pass) {
    auto res = client.loginUser(login, pass);
    Core::user_id = res.second.id;
    return res.first;
}

void Core::logout() {
    Core::user_id = -1;
}

std::vector<Task> Core::getAllTasks() {
    return client.getAllTasks();
}

Solution Core::submitSolution(const int &task_id, const std::string &path_to_file) {
    return client.submitSolution(user_id, task_id, path_to_file);
}

unsigned int Core::createTask(const std::string &desc) {
    return client.createTask(desc);
}


//
// Created by Николай Степанов on 03.05.2023.
//
#include "TaskManager.h"

TaskManager::TaskManager() {

}

Response TaskManager::createTask(const Request &req) {
    return Response();
}

Response TaskManager::getAllTasks(const Request &req) {
    return Response();
}

std::string TaskManager::getParam(const std::string &path, const std::string &name) {
    return std::string();
}

void TaskManager::setService(std::shared_ptr<ITaskService> service) {
    taskService = service;
}

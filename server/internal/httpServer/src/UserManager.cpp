//
// Created by Николай Степанов on 03.05.2023.
//
#include "UserManager.h"

UserManager::UserManager() {

}

Response UserManager::loginUser(const Request &req) {
    return Response();
}

Response UserManager::registerUser(const Request &req) {
    return Response();
}

std::string UserManager::getParam(const std::string &path, const std::string &name) {
    return std::string();
}

void UserManager::setService(std::shared_ptr<IUserService> service) {
    userService = service;
}

//
// Created by Николай Степанов on 03.05.2023.
//
#include "TaskManager.h"

#include "TaskService.h"
#include "TmpTaskService.h"
#include "Utils.h"

TaskManager::TaskManager() : serializer(std::make_shared<Serializer>()), taskService(std::make_shared<TaskService>()) {}

void TaskManager::setService(std::shared_ptr<ITaskService> service) { taskService = service; }

http::message_generator TaskManager::createTask(http::request<http::string_body> &&req) {
    std::string description = serializer->deserialNewTaskData(req.body());

    try {
        taskService->createTask(description, 0.5);
        //    TmpTaskService::createTask(description);
        http::response<http::empty_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.prepare_payload();
        return res;
    } catch (...) {
        return getBadRequest(req, "Something went wrong!");
    }
}

http::message_generator TaskManager::getAllTasks(http::request<http::string_body> &&req) {
    try {
        std::vector<Task> tasks = taskService->getAllTasks();
        //    std::vector<Task> tasks = TmpTaskService::getAllTasks();
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = serializer->serialAllTasks(tasks);
        res.prepare_payload();
        return res;
    } catch (...) {
        return getBadRequest(req, "Something went wrong!");
    }
}

#ifndef APP_HTTPSERVER_HTTPSERVER_MANAGERS_ITaskMANAGER_H_
#define APP_HTTPSERVER_HTTPSERVER_MANAGERS_ITaskMANAGER_H_

#include <memory>
#include <string>

#include "Response.h"
#include "Request.h"
#include "Serializer.h"

class ITaskManager {
public:
    virtual Response createTask(const Request &req) = 0;
    virtual Response getAllTasks(const Request &req) = 0;
};

#endif  // APP_HTTPSERVER_HTTPSERVER_MANAGERS_ITaskMANAGER_H_

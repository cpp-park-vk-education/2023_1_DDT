#ifndef APP_HTTPSERVER_HTTPSERVER_MANAGERS_IUserMANAGER_H_
#define APP_HTTPSERVER_HTTPSERVER_MANAGERS_IUserMANAGER_H_

#include <memory>
#include <string>

#include "Response.h"
#include "Request.h"
#include "Serializer.h"

class IUserManager {
public:
    virtual Response loginUser(const Request &req) = 0;
    virtual Response registerUser(const Request &req) = 0;
};

#endif  // APP_HTTPSERVER_HTTPSERVER_MANAGERS_IUserMANAGER_H_

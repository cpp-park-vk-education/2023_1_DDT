#pragma once

#include <boost/beast.hpp>
#include <iostream>

namespace beast = boost::beast;

void fail(beast::error_code ec, char const* what);

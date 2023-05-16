#include "Utils.h"


void fail(beast::error_code ec, const char *what) {
    std::cerr << what << ": " << ec.message() << "\n";
}

#include "Parser.h"
#include "Request.h"

Parser::Parser()
        : state(method_start) {}

void Parser::reset() {}

boost::tribool Parser::consume(Request& req, char input) {}

bool Parser::isChar(int c) {}

bool Parser::isCtl(int c) {}

bool Parser::isTspecial(int c) {}

bool Parser::isDigit(int c) {}

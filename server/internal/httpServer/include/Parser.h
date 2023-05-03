#ifndef APP_HTTPSERVER_HTTPSERVER_PARSER_H_
#define APP_HTTPSERVER_HTTPSERVER_PARSER_H_

#include "Request.h"

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

class Parser {
 public:
    Parser();
    void reset();

    template <typename InputIterator>
    boost::tuple<boost::tribool, InputIterator> parse(Request& req,
                                                      InputIterator begin, InputIterator end) {
        while (begin != end) {
            boost::tribool result = consume(req, *begin++);
            if (result || !result)
                return boost::make_tuple(result, begin);
        }
        boost::tribool result = boost::indeterminate;
        return boost::make_tuple(result, begin);
    }

 private:
    boost::tribool consume(Request& req, char input);
    static bool isChar(int c);
    static bool isCtl(int c);
    static bool isTspecial(int c);
    static bool isDigit(int c);

    enum state {
        method_start,
        method,
        uri,
        http_version_h,
        http_version_t_1,
        http_version_t_2,
        http_version_p,
        http_version_slash,
        http_version_major_start,
        http_version_major,
        http_version_minor_start,
        http_version_minor,
        expecting_newline_1,
        header_line_start,
        header_lws,
        header_name,
        space_before_header_value,
        header_value,
        expecting_newline_2,
        expecting_newline_3
    } state;
};

#endif  // APP_HTTPSERVER_HTTPSERVER_PARSER_H_

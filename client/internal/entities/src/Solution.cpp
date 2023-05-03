
#include <string>
#include <utility>
#include "Solution.h"

Solution::Solution(unsigned long id, std::string sendDate, unsigned long senderId,
                   std::string source, std::string tokens,
                   std::string astTree, unsigned long taskId,
                   std::string result) : id(id), send_date(std::move(sendDate)), sender_id(senderId),
                                         source(std::move(source)), tokens(std::move(tokens)),
                                         astTree(std::move(astTree)),
                                         task_id(taskId), result(std::move(result)) {}

size_t Solution::getId() const {
    return id;
}


const std::string &Solution::getSendDate() const {
    return send_date;
}

void Solution::setSendDate(const std::string &sendDate) {
    send_date = sendDate;
}

size_t Solution::getSenderId() const {
    return sender_id;
}

void Solution::setSenderId(size_t senderId) {
    sender_id = senderId;
}

const std::string &Solution::getSource() const {
    return source;
}

void Solution::setSource(const std::string &source_) {
    Solution::source = source_;
}

const std::string &Solution::getTokens() const {
    return tokens;
}

void Solution::setTokens(const std::string &tokens_) {
    Solution::tokens = tokens_;
}

const std::string &Solution::getAstTree() const {
    return astTree;
}

void Solution::setAstTree(const std::string &astTree_) {
    Solution::astTree = astTree_;
}

size_t Solution::getTaskId() const {
    return task_id;
}

void Solution::setTaskId(size_t taskId) {
    task_id = taskId;
}

const std::string &Solution::getResult() const {
    return result;
}

void Solution::setResult(const std::string &result_) {
    Solution::result = result_;
}
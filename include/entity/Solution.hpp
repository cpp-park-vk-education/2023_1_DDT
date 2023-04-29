#ifndef SOURCEDOUT_SOLUTION_HPP
#define SOURCEDOUT_SOLUTION_HPP
#include <iostream>
#include <string>
#include <utility>

class Solution{
private:
    size_t id;
    std::string send_date;
    size_t sender_id;
    std::string source;
    size_t task_id;
    std::string result;
public:
    Solution(size_t id, std::string sendDate, size_t senderId, std::string source, size_t taskId,
             std::string result) : id(id), send_date(std::move(sendDate)), sender_id(senderId), source(std::move(source)),
                                          task_id(taskId), result(std::move(result)) {}

    [[nodiscard]] size_t getId() const {
        return id;
    }


    [[nodiscard]] const std::string &getSendDate() const {
        return send_date;
    }

    void setSendDate(const std::string &sendDate) {
        send_date = sendDate;
    }

    [[nodiscard]] size_t getSenderId() const {
        return sender_id;
    }

    void setSenderId(size_t senderId) {
        sender_id = senderId;
    }

    [[nodiscard]] const std::string &getSource() const {
        return source;
    }

    void setSource(const std::string &source_) {
        Solution::source = source_;
    }

    [[nodiscard]] size_t getTaskId() const {
        return task_id;
    }

    void setTaskId(size_t taskId) {
        task_id = taskId;
    }

    [[nodiscard]] const std::string &getResult() const {
        return result;
    }

    void setResult(const std::string &result_) {
        Solution::result = result_;
    }
};
#endif //SOURCEDOUT_SOLUTION_HPP

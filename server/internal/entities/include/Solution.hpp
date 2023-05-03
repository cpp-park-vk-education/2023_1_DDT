#ifndef SOURCEDOUT_SOLUTION_HPP
#define SOURCEDOUT_SOLUTION_HPP

#include <iostream>
#include <string>
#include <utility>

class Solution {
public:
    Solution(size_t id, std::string sendDate, size_t senderId, std::string source,
             std::string tokens, std::string astTree, size_t taskId, std::string result);

    [[nodiscard]] size_t getId() const;


    [[nodiscard]] const std::string &getSendDate() const;

    void setSendDate(const std::string &sendDate);

    [[nodiscard]] size_t getSenderId() const;

    void setSenderId(size_t senderId);

    [[nodiscard]] const std::string &getSource() const;

    void setSource(const std::string &source);

    [[nodiscard]] const std::string &getTokens() const;

    void setTokens(const std::string &tokens);

    [[nodiscard]] const std::string &getAstTree() const;

    void setAstTree(const std::string &astTree);

    [[nodiscard]] size_t getTaskId() const;

    void setTaskId(size_t taskId);

    [[nodiscard]] const std::string &getResult() const;

    void setResult(const std::string &result);

    void setId(size_t id);

    bool operator==(const Solution &rhs) const;

    bool operator!=(const Solution &rhs) const;

private:
    size_t id;
    std::string send_date;
    size_t sender_id;
    std::string source;
    std::string tokens;
    std::string astTree;
    size_t task_id;
    std::string result;
public:

};

#endif //SOURCEDOUT_SOLUTION_HPP

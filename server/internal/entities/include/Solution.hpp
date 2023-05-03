#ifndef SOURCEDOUT_SOLUTION_HPP
#define SOURCEDOUT_SOLUTION_HPP

#include <iostream>
#include <string>
#include <utility>

class Solution {
public:
    Solution(size_t id, std::string sendDate, size_t senderId, std::string source,
             std::string tokens, std::string astTree, size_t taskId, std::string result) noexcept;

    Solution(std::string sendDate, size_t senderId, std::string source, std::string tokens, std::string astTree,
             size_t taskId, std::string result) noexcept;
    Solution() noexcept;

    [[nodiscard]] size_t getId() const noexcept;


    [[nodiscard]] const std::string &getSendDate() const noexcept;

    void setSendDate(const std::string &sendDate) noexcept;

    [[nodiscard]] size_t getSenderId() const noexcept;

    void setSenderId(size_t senderId) noexcept;

    [[nodiscard]] const std::string &getSource() const noexcept;

    void setSource(const std::string &source) noexcept;

    [[nodiscard]] const std::string &getTokens() const noexcept;

    void setTokens(const std::string &tokens) noexcept;

    [[nodiscard]] const std::string &getAstTree() const noexcept;

    void setAstTree(const std::string &astTree) noexcept;

    [[nodiscard]] size_t getTaskId() const noexcept;

    void setTaskId(size_t taskId) noexcept;

    [[nodiscard]] const std::string &getResult() const noexcept;

    void setResult(const std::string &result) noexcept;

    void setId(size_t id) noexcept;

    bool operator==(const Solution &rhs) const noexcept;

    bool operator!=(const Solution &rhs) const noexcept;

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

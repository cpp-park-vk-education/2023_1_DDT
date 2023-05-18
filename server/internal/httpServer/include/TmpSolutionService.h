#pragma once

#include <vector>
#include <string>
#include "Solution.hpp"

class TmpSolutionService {
public:
    static Solution createSolution(std::size_t user_id, std::size_t task_id, std::string source) {
        count++;
        Solution sol(count, "", user_id, source, task_id,"ok", "", "", 1);
        for (auto& i: solutions) {
            if (i.getSource() == source && i.getTaskId() == task_id && i.getSenderId() != user_id)
                sol.setResult("plagiat");
        }
        solutions.push_back(sol);
        return sol;
    }

    static std::size_t count;
    static std::vector<Solution> solutions;
};

std::vector<Solution> TmpSolutionService::solutions = {};
std::size_t TmpSolutionService::count = 3;

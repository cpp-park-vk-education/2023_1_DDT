#ifndef SOURCEDOUT_ISOLUTIONREPOSITORY_HPP
#define SOURCEDOUT_ISOLUTIONREPOSITORY_HPP

#include <iostream>
#include <vector>
#include "../Solution.hpp"

class ISolutionRepository {
    virtual Solution getSolutionById(size_t id) = 0;

    virtual std::vector<Solution> getSolutionsBySenderId(size_t sender_id) = 0;

    virtual std::vector<Solution> getSolutionsByTaskId(size_t task_id) = 0;

    virtual void storeSolution(Solution solution) = 0;

    virtual void updateSolution(Solution solution) = 0;

    virtual void deleteSolutionById(size_t id) = 0;

    virtual void deleteSolution(Solution solution) = 0;


};

#endif //SOURCEDOUT_ISOLUTIONREPOSITORY_HPP

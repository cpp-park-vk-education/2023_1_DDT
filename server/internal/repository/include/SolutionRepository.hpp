#ifndef SOURCEDOUT_SOLUTIONREPOSITORY_HPP
#define SOURCEDOUT_SOLUTIONREPOSITORY_HPP

#include <iostream>
#include <pqxx/pqxx>
#include <boost/format.hpp>
#include <fstream>
#include "ISolutionRepository.hpp"
#include "dbManager.hpp"
#include <optional>


using namespace pqxx;


class SolutionRepository : public ISolutionRepository {

public:
    explicit SolutionRepository();
    std::optional<Solution> getSolutionById(size_t id) override;

    std::vector<Solution> getSolutionsBySenderId(size_t sender_id) override;

    std::vector<Solution> getSolutionsByTaskId(size_t task_id)  override;

    size_t storeSolution(Solution solution) override;

    void updateSolution(Solution solution) override;

    void deleteSolutionById(size_t id)  override;

    void deleteSolution(Solution solution)  override;

    std::optional<Solution> getOriginalSolution(size_t id) override;

private:
    static Solution makeSolution(const result::const_iterator& c);
    std::shared_ptr<dbManager> manager;
};

#endif

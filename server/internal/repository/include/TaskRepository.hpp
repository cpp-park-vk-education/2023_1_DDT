#ifndef SOURCEDOUT_TASKREPOSITORY_HPP
#define SOURCEDOUT_TASKREPOSITORY_HPP

#include <boost/format.hpp>
#include <fstream>
#include "ITaskRepository.hpp"
#include "pqxx/pqxx"
#include "dbManager.hpp"

using namespace pqxx;

class TaskRepository : ITaskRepository {
public:
    Task getTaskById(size_t id) override;

    void updateTask(Task task) override;

    size_t storeTask(Task task) override;

    void deleteTask(Task task) override;

    void deleteTaskById(size_t task_id) override;

private:
    static Task makeTask(const result::const_iterator &c);
    std::shared_ptr<dbManager> manager;
};

#endif //SOURCEDOUT_TASKREPOSITORY_HPP

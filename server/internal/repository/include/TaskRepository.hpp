#ifndef SOURCEDOUT_TASKREPOSITORY_HPP
#define SOURCEDOUT_TASKREPOSITORY_HPP

#include <boost/format.hpp>
#include <fstream>
#include "../virtual/ITaskRepository.hpp"
#include "pqxx/pqxx"

using namespace pqxx;

class TaskRepository : ITaskRepository {
public:
    Task getTaskById(size_t id) override;

    void updateTask(Task task) override;

    void storeTask(Task task) override;

    void deleteTask(Task task) override;

    void deleteTaskById(size_t task_id) override;

private:
    static Task makeTask(const result::const_iterator &c);
};

#endif //SOURCEDOUT_TASKREPOSITORY_HPP

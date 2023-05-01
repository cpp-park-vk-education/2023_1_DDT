#ifndef SOURCEDOUT_USERREPOSITORY_HPP
#define SOURCEDOUT_USERREPOSITORY_HPP

#include <iostream>
#include "../virtual/IUserRepository.hpp"
#include <pqxx/pqxx>
#include <boost/format.hpp>
#include <fstream>
#include "conn.hpp"
using namespace pqxx;

class UserRepository : IUserRepository {
public:
    explicit UserRepository(conn connect);

    User getUserById(size_t id) override;

    User getUserByLogin(std::string login) override;

    size_t makeUser(User user) override;

    void deleteUser(User user) override;

    void deleteByUserId(size_t user_id) override;

    std::vector<User> getAllUsers() override;


private:
    static User makeUser(const result::const_iterator& c);
    conn conn_;
};

#endif //SOURCEDOUT_USERREPOSITORY_HPP

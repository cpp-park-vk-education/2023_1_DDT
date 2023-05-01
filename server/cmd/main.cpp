

#include "../internal/repository/include/UserRepository.hpp"

int main(){
    User user{"qwerty200468@gmail.com", "123", "tolik"};
    conn conn;
    UserRepository repo(conn);
    std::cout<<conn.getData();
    repo.makeUser(user);
}
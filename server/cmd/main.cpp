//#include "dotenv.h"
#include "UserRepository.hpp"
#include "User.hpp"

//using namespace dotenv;
int main(){
    User user{"qwerty200468@gmail.com", "123", "tolik"};
    UserRepository repo;
    std::cout<<repo.getUserById(1)<<std::endl;
}
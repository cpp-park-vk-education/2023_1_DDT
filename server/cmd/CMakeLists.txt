cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "Server")

project(${PROJECT_NAME})

add_executable(Server main.cpp)
message(STATUS ${libusers})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${antlr4-runtime_LIBRARIES} ${libpqxx_LIBRARIES} ${libEntities_LIB} ${libRepository_LIB})
target_include_directories(Server PUBLIC ${libusers_INCLUDE_DIRS})
message("Built server")


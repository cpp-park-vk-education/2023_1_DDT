set(CMAKE_PREFIX_PATH build)
project(SourcedOut CXX)
find_package(Boost 1.8.1 REQUIRED)
find_package(Threads REQUIRED)
find_library(PQXX_LIB pqxx)
find_package(GTest REQUIRED)
find_package(nlohmann_json REQUIRED)
message(STATUS ${nlohmann_json_LIBRARIES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(pkg)
add_subdirectory(internal)
add_subdirectory(cmd)

message(STATUS ${Boost_LIBRARIES})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-lpthread -pthread")


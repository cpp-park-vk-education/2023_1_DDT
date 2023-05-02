cmake_minimum_required(VERSION 3.16)
project(test_service)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-coverage)

file(GLOB SOURCES *.cpp)

enable_testing()
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SERVICE_lib_LIBRARY} GTest::GTest gmock pthread)
target_include_directories(${PROJECT_NAME} PUBLIC ${SERVICE_lib_INCLUDE_DIRS})


add_test(test_service test_service)
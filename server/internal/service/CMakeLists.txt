cmake_minimum_required(VERSION 3.19)

project("ServiceLib")

file(GLOB SOURCES ./src/*.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include /home/denis/2023_1_DDT/antlr/virtual)


include_directories(${INCLUDE_DIRS})
add_library(${PROJECT_NAME} ${SOURCES})

# target_link_libraries(${LIB_NAME})

set(SERVICE_LIBRARY ${PROJECT_NAME} PARENT_SCOPE)
set(SERVICE_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)


enable_testing()
add_subdirectory(tests)
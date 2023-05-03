cmake_minimum_required(VERSION 3.7)
project(cpp_antlr_lib)

file(GLOB SOURCES ./src/*.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/../virtual)


include_directories(${INCLUDE_DIRS})
add_library(${PROJECT_NAME} ${SOURCES})


target_link_libraries(${PROJECT_NAME} antlr4_static Threads::Threads)

set(CPP_ANTLR_LIBRARY ${PROJECT_NAME})
set(CPP_ANTLR_LIBRARY ${CPP_ANTLR_LIBRARY} PARENT_SCOPE)

set(CPP_ANTLR_INCLUDE_DIRS ${INCLUDE_DIRS})
set(CPP_ANTLR_INCLUDE_DIRS ${CPP_ANTLR_INCLUDE_DIRS} PARENT_SCOPE)

message("CPP_ANTLR = ${CPP_ANTLR_INCLUDE_DIRS} ")
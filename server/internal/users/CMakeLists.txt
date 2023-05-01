set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.19)
project(users)

set(LIB_NAME libusers)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/virtual/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/virtual/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

message("SOURCES = ${SOURCES}")
message("HEADERS = ${HEADERS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g -Wall -Wextra -O2 -pedantic -Wformat=2 -Wfloat-equal -Wconversion \
-Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

add_library(${LIB_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/virtual)
target_link_libraries(${LIB_NAME} ${Boost_LIBRARIES} ${libpqxx_LIBRARIES} ${DB_Lib_LIB})

set(libusers_LIB ${LIB_NAME})
set(libusers_LIB ${libusers_LIB} PARENT_SCOPE)
set(libusers_INCLUDE_DIRS ${LIB_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/virtual)
set(libusers_INCLUDE_DIRS ${libusers_INCLUDE_DIRS} PARENT_SCOPE)

enable_testing()
add_subdirectory(tests)
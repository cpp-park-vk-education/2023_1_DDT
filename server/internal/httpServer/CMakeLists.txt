project("HttpServerLib")

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/virtual)
file(GLOB INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/virtual/*.h)

include_directories(${INCLUDE_DIRS} ${Boost_INCLUDE_DIR} ${libRepository_INCLUDE_DIRS} ${ANTLR4_LIB_INCLUDE_DIRS} ${libEntities_INCLUDE_DIRS} ${SERVICE_lib_INCLUDE_DIRS} ${METRICS_lib_INCLUDE_DIRS})
add_library(${PROJECT_NAME} ${SOURCES} ${INCLUDES})
add_executable(HttpServer_run main.cpp)

target_link_libraries(${PROJECT_NAME} ${SERVICE_lib_LIB} ${libEntities_LIB} ${Boost_LIBRARIES})
target_link_libraries(HttpServer_run ${PROJECT_NAME} ${Boost_LIBRARIES} ${libpqxx_LIBRARIES} ${SERVICE_lib_LIB} ${libRepository_LIB} ${libEntities_LIB} ${ANTLR4_LIB} ${METRICS_LIBRARY})

set(HTTPSERVER_LIB ${PROJECT_NAME})
set(HTTPSERVER_LIB ${HTTPSERVER_LIB} PARENT_SCOPE)

set(HTTPSERVER_INCLUDE_DIRS ${INCLUDE_DIRS})
set(HTTPSERVER_INCLUDE_DIRS ${HTTPSERVER_INCLUDE_DIRS} PARENT_SCOPE)

#enable_testing()
#add_subdirectory(tests)
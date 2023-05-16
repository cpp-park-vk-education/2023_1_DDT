set(PROJECT_NAME "Server")

project(${PROJECT_NAME})

add_executable(Server main.cpp)
message(STATUS ${libusers})
message("${SERVICE_LIB}")
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${libpqxx_LIBRARIES} ${SERVICE_LIB} ${libEntities_LIB} ${libRepository_LIB})
target_include_directories(Server PUBLIC ${SERVICE_lib_INCLUDE_DIRS} ${libusers_INCLUDE_DIRS})

message("Built server")


set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.19)
add_subdirectory(entities)
add_subdirectory(dbManager)
add_subdirectory(repository)
set(libEntities_LIB ${libEntities_LIB} PARENT_SCOPE)
set(libEntities_INCLUDE_DIRS ${libEntities_INCLUDE_DIRS} PARENT_SCOPE)

set(libRepository_LIB ${libRepository_LIB} PARENT_SCOPE)
set(libRepository_INCLUDE_DIRS ${libRepository_INCLUDE_DIRS} PARENT_SCOPE)

set(libDbManager_LIB ${libDbManager_LIB} PARENT_SCOPE)
set(libDbManager_INCLUDE_DIRS ${libDbManager_INCLUDE_DIRS} PARENT_SCOPE)

message("DbManager = ${libDbManager_LIB}")
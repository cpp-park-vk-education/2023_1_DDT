add_subdirectory(src)
add_subdirectory(entities)
add_subdirectory(dbManager)
add_subdirectory(repository)
add_subdirectory(service)
add_subdirectory(httpServer)

set(libEntities_LIB ${libEntities_LIB} PARENT_SCOPE)
set(libEntities_INCLUDE_DIRS ${libEntities_INCLUDE_DIRS} PARENT_SCOPE)

set(libRepository_LIB ${libRepository_LIB} PARENT_SCOPE)
set(libRepository_INCLUDE_DIRS ${libRepository_INCLUDE_DIRS} PARENT_SCOPE)

set(SERVICE_LIB ${SERVICE_lib_LIB} PARENT_SCOPE)
set(SERVICE_INCLUDE_DIRS ${SERVICE_lib_INCLUDE_DIRS} PARENT_SCOPE)

set(libDbManager_LIB ${libDbManager_LIB} PARENT_SCOPE)
set(libDbManager_INCLUDE_DIRS ${libDbManager_INCLUDE_DIRS} PARENT_SCOPE)

set(HTTPSERVER_lib_LIB ${HTTPSERVER_lib_LIB} PARENT_SCOPE)
set(HTTPSERVER_lib_INCLUDE_DIRS ${HTTPSERVER_lib_INCLUDE_DIRS} PARENT_SCOPE)

message("DbManager = ${libDbManager_LIB}")
message("HTTPSERVER = " ${HTTPSERVER_lib_LIB})

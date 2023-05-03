add_subdirectory(entities)
add_subdirectory(httpClient)

set(libClientEntities_LIB ${libClientEntities_LIB} PARENT_SCOPE)
set(libClientEntities_INCLUDE_DIRS ${libClientEntities_INCLUDE_DIRS} PARENT_SCOPE)

set(HTTPCLIENT_lib_LIB ${HTTPCLIENT_lib_LIB} PARENT_SCOPE)
set(HTTPCLIENT_lib_INCLUDE_DIRS ${HTTPCLIENT_lib_INCLUDE_DIRS} PARENT_SCOPE)
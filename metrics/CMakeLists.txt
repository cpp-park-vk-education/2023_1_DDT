add_library(MetricsLib source/TextMetricImpl.cpp source/TokenMetricImpl.cpp)

target_include_directories(MetricsLib PUBLIC metrics_headers)
target_link_libraries(MetricsLib PUBLIC ${Boost_LIBRARIES})

add_custom_target(
        ${PROJECT_NAME}_COVERAGE
        COMMAND gcovr ${CMAKE_CURRENT_BINARY_DIR} -r ${CMAKE_CURRENT_SOURCE_DIR}
)

#if(BUILD_TESTS)
add_subdirectory(tests)
#endif()
add_library(MetricsLib source/TextMetricImpl.cpp)

target_include_directories(MetricsLib PUBLIC metrics_headers)
target_link_libraries(MetricsLib PUBLIC ${Boost_LIBRARIES})
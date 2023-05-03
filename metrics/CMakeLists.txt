add_library(MetricsLib source/TextMetricImpl.cpp)
find_package(Boost 1.8.1 REQUIRED)

target_include_directories(MetricsLib PUBLIC metrics_headers)
target_link_libraries(MetricsLib PUBLIC ${Boost_LIBRARIES})
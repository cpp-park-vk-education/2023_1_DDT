find_package(Boost 1.8.1 REQUIRED)
add_library(MetricsLib source/TextMetricImpl.cpp)

target_include_directories(MetricsLib PUBLIC metrics_headers ${Boost_LIBRARIES})
add_executable(metrics_test src/text_metrics_tests.cpp)

target_link_libraries(metrics_test MetricsLib  GTest::gtest_main GTest::gmock)

add_test(metrics_test metrics_test)
//
// Created by march on 04.05.2023.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

#include "TextMetricsLib.h"

class LevDistTextMetricTest : public ::testing::Test {
protected:
    std::unique_ptr <LevDistTextMetric> levDistTextMetric;
    void SetUp(){
        levDistTextMetric = std::make_unique <LevDistTextMetric>();
    }
    void TearDown(){}
};

class JaccardTextMetricTest : public ::testing::Test {
protected:
    std::unique_ptr <JaccardTextMetric> jaccardTextMetric;
    void SetUp(){
        jaccardTextMetric = std::make_unique <JaccardTextMetric>();
    }
    void TearDown(){}
};

TEST_F(LevDistTextMetricTest, check_eq_progs) {
    std::ifstream fin1;
    fin1.open("src/test-codes/code1.txt");

    std::string text1( (std::istreambuf_iterator<char>(fin1) ),
                       (std::istreambuf_iterator<char>()    ) );

    fin1.close();
    levDistTextMetric->setData(text1, text1);

    EXPECT_EQ(levDistTextMetric->getMetric(), 1);
}

TEST_F(LevDistTextMetricTest, check_absolutely_not_eq_progs) {

    levDistTextMetric->setData("a b c", "d e f g");

    EXPECT_EQ(levDistTextMetric->getMetric() < 0.5, true);
}

TEST_F(LevDistTextMetricTest, test_with_empty_prog) {

    levDistTextMetric->setData("a b c", "");

    EXPECT_EQ(levDistTextMetric->getMetric(), 0);
}

TEST_F(JaccardTextMetricTest, check_eq_progs){
    std::ifstream fin1;
    fin1.open("src/test-codes/code1.txt");

    std::string text1( (std::istreambuf_iterator<char>(fin1) ),
                       (std::istreambuf_iterator<char>()    ) );

    fin1.close();
    jaccardTextMetric->setData(text1, text1);

    EXPECT_EQ(jaccardTextMetric->getMetric(), 1);
}

TEST_F(JaccardTextMetricTest, check_absolutely_not_eq_progs) {

    jaccardTextMetric->setData("a b c", "d e f g");

    EXPECT_EQ(jaccardTextMetric->getMetric(), 0);
}

TEST_F(JaccardTextMetricTest, test_with_empty_prog) {

    jaccardTextMetric->setData("a b c", "");

    EXPECT_EQ(jaccardTextMetric->getMetric(), 0);
}




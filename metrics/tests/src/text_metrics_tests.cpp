//
// Created by march on 04.05.2023.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

#include "TextMetricsLib.h"

class LivDistTextMetricTest : public ::testing::Test {
protected:
    std::unique_ptr <LivDistTextMetric> livDistTextMetric;
    void SetUp(){
        livDistTextMetric = std::make_unique <LivDistTextMetric>();
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



TEST_F(LivDistTextMetricTest, check_eq_progs) {
    std::ifstream fin1;
    fin1.open("src/test-codes/code1.txt");

    std::string text1( (std::istreambuf_iterator<char>(fin1) ),
                       (std::istreambuf_iterator<char>()    ) );

    fin1.close();
    livDistTextMetric->setData(text1, text1);
    livDistTextMetric->countMetric();

    EXPECT_EQ(livDistTextMetric->getMetric(), 1);
}

TEST_F(LivDistTextMetricTest, check_absolutely_not_eq_progs) {

    livDistTextMetric->setData("a b c", "d e f g");
    livDistTextMetric->countMetric();

    EXPECT_EQ(livDistTextMetric->getMetric() < 0.5, true);
}

TEST_F(LivDistTextMetricTest, test_with_empty_prog) {

    livDistTextMetric->setData("a b c", "");
    livDistTextMetric->countMetric();

    EXPECT_EQ(livDistTextMetric->getMetric(), 0);
}

TEST_F(JaccardTextMetricTest, check_eq_progs){
    std::ifstream fin1;
    fin1.open("src/test-codes/code1.txt");

    std::string text1( (std::istreambuf_iterator<char>(fin1) ),
                       (std::istreambuf_iterator<char>()    ) );

    fin1.close();
    jaccardTextMetric->setData(text1, text1);
    jaccardTextMetric->countMetric();

    EXPECT_EQ(jaccardTextMetric->getMetric(), 1);
}

TEST_F(JaccardTextMetricTest, check_absolutely_not_eq_progs) {

    jaccardTextMetric->setData("a b c", "d e f g");
    jaccardTextMetric->countMetric();

    EXPECT_EQ(jaccardTextMetric->getMetric(), 0);
}

TEST_F(JaccardTextMetricTest, test_with_empty_prog) {

    jaccardTextMetric->setData("a b c", "");
    jaccardTextMetric->countMetric();

    EXPECT_EQ(jaccardTextMetric->getMetric(), 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}


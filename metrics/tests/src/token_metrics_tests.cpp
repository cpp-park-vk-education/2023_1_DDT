//
// Created by march on 16.05.2023.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>

#include "TokenMetricLib.h"

class LevDistTokenMetricTest : public ::testing::Test {
protected:
    std::unique_ptr <LevDistTokenMetric> levDistTokenMetric;
    void SetUp(){
        levDistTokenMetric = std::make_unique <LevDistTokenMetric>();
    }
    void TearDown(){}
};

class WShinglingTokenMetricTest : public ::testing::Test {
protected:
    std::unique_ptr <WShinglingTokenMetric> wShinglingTokenMetric;
    void SetUp(){
        wShinglingTokenMetric = std::make_unique <WShinglingTokenMetric>();
    }
    void TearDown(){}
};

TEST_F(LevDistTokenMetricTest, check_eq_progs) {

    std::vector <int> tokens1 = {1, 2, 3};

    levDistTokenMetric->setData(tokens1, tokens1);

    EXPECT_EQ(levDistTokenMetric->getMetric(), 1);
}

TEST_F(LevDistTokenMetricTest, check_absolutely_not_eq_progs) {

    std::vector <int> tokens1 = {1, 2, 3};
    std::vector <int> tokens2 = {3, 4, 5, 6};

    levDistTokenMetric->setData(tokens1, tokens2);

    EXPECT_EQ(levDistTokenMetric->getMetric() < 0.5, true);
}

TEST_F(LevDistTokenMetricTest, test_with_empty_prog) {

    std::vector <int> tokens1 = {1, 2, 3};
    std::vector <int> tokens2 = {};

    levDistTokenMetric->setData(tokens1, tokens2);

    EXPECT_EQ(levDistTokenMetric->getMetric(), 0);
}

TEST_F(WShinglingTokenMetricTest, check_eq_progs){

    std::vector <int> tokens1 = {1, 2, 3, 4, 5, 6};
    std::vector <int> tokens2 = {1, 2, 3, 4, 5, 6};

    wShinglingTokenMetric->setData(tokens1, tokens1);

    EXPECT_EQ(wShinglingTokenMetric->getMetric(), 1);
}

TEST_F(WShinglingTokenMetricTest, check_absolutely_not_eq_progs) {

    std::vector <int> tokens1 = {1, 2, 3};
    std::vector <int> tokens2 = {4, 5, 6, 1};

    wShinglingTokenMetric->setData(tokens1, tokens1);

    EXPECT_EQ(wShinglingTokenMetric->getMetric(), 0);
}

TEST_F(WShinglingTokenMetricTest, test_with_empty_prog) {

    std::vector <int> tokens1 = {1, 2, 3};
    std::vector <int> tokens2 = {};

    wShinglingTokenMetric->setData(tokens1, tokens1);

    EXPECT_EQ(wShinglingTokenMetric->getMetric(), 0);
}






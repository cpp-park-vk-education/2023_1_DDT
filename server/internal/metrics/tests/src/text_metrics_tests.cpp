//
// Created by march on 04.05.2023.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

#include "TextMetricsLib.h"
#include "TokenMetricLib.h"

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

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}


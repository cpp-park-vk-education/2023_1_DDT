//
// Created by march on 04.05.2023.
//

#ifndef SOURCEDOUT_TOKENMETRICLIB_H
#define SOURCEDOUT_TOKENMETRICLIB_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

#include <boost/tokenizer.hpp>


class ITokenMetric{
    virtual void countMetric() = 0;
    virtual void setData(std::vector<std::string> tokens1, std::vector<std::string> tokens2) = 0;
    virtual double getMetric() = 0;
};

class PrepareDataTokenMetric : public ITokenMetric{
public:
    void setData(std::vector<std::string> _tokens1, std::vector<std::string> _tokens2) override;
    double getMetric() override;
protected:
    std::vector <std::string> tokens1;
    std::vector <std::string> tokens2;
    double metric_res{};
};

class LivDistTokenMetric : public PrepareDataTokenMetric{
public:
    void countMetric() override;
};

class WShinglingTokenMetric : public PrepareDataTokenMetric{
public:
    void countMetric() override;
};

#endif //SOURCEDOUT_TOKENMETRICLIB_H

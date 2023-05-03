//
// Created by march on 02.05.2023.
//

#ifndef SOURCEDOUT_DECLARATION_H
#define SOURCEDOUT_DECLARATION_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

#include <boost/tokenizer.hpp>


class ITextMetric{
    virtual void countMetric() = 0;
    virtual void getData(std::string text1, std::string text2) = 0;
    virtual double getMetric() = 0;
};

class PrepareDataTextMetric : public ITextMetric{
public:
    void getData(std::string text1, std::string text2) override;
    double getMetric() override;
protected:
    std::vector <std::string> tokens1;
    std::vector <std::string> tokens2;
    double metric_res;
private:
    static std::string deleteComments(const std::string& text);
    static std::vector <std::string> tbmTokenizer(const std::string &text);
};

class LivDistTextMetric : public PrepareDataTextMetric{
public:
    void countMetric() override;
};

class JaccardTextMetric : public PrepareDataTextMetric{
public:
    void countMetric() override;
};


#endif //SOURCEDOUT_DECLARATION_H

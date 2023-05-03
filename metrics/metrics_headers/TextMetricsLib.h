//
// Created by march on 02.05.2023.
//

#ifndef SOURCEDOUT_DECLARATION_H
#define SOURCEDOUT_DECLARATION_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <boost/tokenizer.hpp>


class ITextMetric{
    virtual double countMetric() = 0;
    virtual void getData(std::istream& fin1, std::istream& fin2) = 0;
};

class PrepareDataTextMetric : public ITextMetric{
public:
    void getData(std::istream& fin1, std::istream& fin2);
protected:
    std::vector <std::string> tokens1;
    std::vector <std::string> tokens2;
    static std::string deleteComments(const std::string& text);
    std::vector <std::string> tbmTokenizer(const std::string &text);
};

class LivDistTextMetric : public PrepareDataTextMetric{
public:
    double countMetric();


private:
    std::vector <std::string> tokens1;
    std::vector <std::string> tokens2;
};


#endif //SOURCEDOUT_DECLARATION_H

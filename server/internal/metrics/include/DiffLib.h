//
// Created by march on 22.05.2023.
//

#ifndef SOURCEDOUT_DIFFLIB_H
#define SOURCEDOUT_DIFFLIB_H

#include <boost/tokenizer.hpp>
#include <iostream>
#include <set>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>

class FoundSame {
public:
    void setData(std::string text1, std::string text2);
    void setData2(std::vector <std::string> _tokens1, std::vector <std::string> _tokens2);
    void tokens2text();
    [[maybe_unused]] std::pair <std::string, std::string> getTexts();

private:
    struct Elem {
        std::string op; // 1 - Insert, 2 - Delete, 3 - Copy, 4 - Replace
        std::string token1;
        std::string token2;
    };

    std::vector <std::string> tokens1;
    std::vector <std::string> tokens2;
    std::vector <Elem> res_alignment;

    static std::vector <std::string> diffTokenizer(const std::string& text);
    static std::string delServSimbols(std::string s);
};

#endif //SOURCEDOUT_DIFFLIB_H

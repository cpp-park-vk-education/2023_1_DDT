#include <iostream>

#include "PythonAntlr.h"
#include "MyCppAntlr.h"
#include "TextMetricsLib.h"

int main(int argc, const char* argv[]) {
    //   ifstream ins("/home/denis/2023_1_DDT/antlr/test.py");
    std::ifstream fin1("internal/metrics/testProgs/cpp/code1.txt");
    std::ifstream fin2("internal/metrics/testProgs/cpp/code2.txt");

    assert(fin1.is_open());
    assert(fin2.is_open());

    std::string text1( (std::istreambuf_iterator<char>(fin1) ),
                       (std::istreambuf_iterator<char>()    ) );

    std::string text2( (std::istreambuf_iterator<char>(fin2) ),
                       (std::istreambuf_iterator<char>()    ) );

    LevDistTextMetric livDistTextMetric;
    JaccardTextMetric jaccardTextMetric;

    std::cout << "Text-based results:" << std::endl;
    livDistTextMetric.setData(text1, text2);
    jaccardTextMetric.setData(text1, text2);

    std::cout << livDistTextMetric.getMetric() << std::endl << jaccardTextMetric.getMetric() << std::endl;

    fin1.close();
    fin2.close();

    std::ifstream fin3("internal/metrics/testProgs/cpp/code1.txt");
    std::ifstream fin4("internal/metrics/testProgs/cpp/code2.txt");


    MyCppAntlr cppA1 = MyCppAntlr(fin3);
    MyCppAntlr cppA2 = MyCppAntlr(fin4);

    std::vector<std::string> tokens1 = cppA1.getTokensArray();
    std::vector<std::string> tokens2 = cppA2.getTokensArray();

    std::cout << "Tokens1:" << std::endl;
    for (const std::string& token : tokens1) {
        std::cout << token << std::endl;
    }
    std::cout << "Tokens2:" << std::endl;
    for (const std::string& token : tokens2) {
        std::cout << token << std::endl;
    }

    std::cout << cppA1.getTreeString() << std::endl;
    std::cout << cppA2.getTreeString() << std::endl;

    fin3.close();
    fin4.close();

    return 0;
}
#include <iostream>
#include "TextMetricsLib.h"
#include <fstream>

int main(){
    std::ifstream fin1;
    fin1.open("metrics/code1.txt");
    assert(fin1.is_open());

    std::ifstream fin2;
    fin2.open("metrics/code2.txt");
    assert(fin2.is_open());

    std::string text1( (std::istreambuf_iterator<char>(fin1) ),
                       (std::istreambuf_iterator<char>()    ) );

    std::string text2( (std::istreambuf_iterator<char>(fin2) ),
                       (std::istreambuf_iterator<char>()    ) );
    fin1.close();
    fin2.close();

    LivDistTextMetric livDistTextMetric;
    JaccardTextMetric jaccardTextMetric;

    livDistTextMetric.getData(text1, text2);
    jaccardTextMetric.getData(text1, text2);

    livDistTextMetric.countMetric();
    jaccardTextMetric.countMetric();

    std::cout << livDistTextMetric.getMetric() << std::endl << jaccardTextMetric.getMetric();
}
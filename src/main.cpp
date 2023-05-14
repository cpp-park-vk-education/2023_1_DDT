#include <iostream>
#include <fstream>

#include "TextMetricsLib.h"

int main(){
    std::ifstream fin1;
    fin1.open("metrics/testProgs/code1.txt");
    assert(fin1.is_open());

    std::ifstream fin2;
    fin2.open("metrics/testProgs/code2.txt");
    assert(fin2.is_open());

    std::string text1( (std::istreambuf_iterator<char>(fin1) ),
                       (std::istreambuf_iterator<char>()    ) );

    std::string text2( (std::istreambuf_iterator<char>(fin2) ),
                       (std::istreambuf_iterator<char>()    ) );
    fin1.close();
    fin2.close();

    LevDistTextMetric livDistTextMetric;
    JaccardTextMetric jaccardTextMetric;

    livDistTextMetric.setData(text1, text2);
    jaccardTextMetric.setData(text1, text2);

    std::cout << livDistTextMetric.getMetric() << std::endl << jaccardTextMetric.getMetric();
}
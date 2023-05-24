#include <iostream>

#include "PythonAntlr.h"
#include "MyCppAntlr.h"
#include "TokenMetricLib.h"
#include "TextMetricsLib.h"
#include "DiffLib.h"

int main(int argc, const char* argv[]) {
  //   ifstream ins("/home/denis/2023_1_DDT/antlr/test.py");
  std::ifstream fin1("internal/metrics/testProgs/cpp/code1.txt");
  std::ifstream fin2("internal/metrics/testProgs/cpp/code2.txt");


  std::string text1( (std::istreambuf_iterator<char>(fin1) ),
                     (std::istreambuf_iterator<char>()    ) );

  std::string text2( (std::istreambuf_iterator<char>(fin2) ),
                     (std::istreambuf_iterator<char>()    ) );

  LevDistTextMetric livDistTextMetric;
  JaccardTextMetric jaccardTextMetric;

  livDistTextMetric.setData(text1, text2);
  jaccardTextMetric.setData(text1, text2);

  std::cout << livDistTextMetric.getMetric() << std::endl << jaccardTextMetric.getMetric() << std::endl;

  FoundSame foundSame;
  foundSame.setData(text1, text2);
 // std::pair <std::string, std::string> res = foundSame.getTexts();

  fin1.close();
  fin2.close();

  std::ifstream fin3("internal/metrics/testProgs/cpp/code1.txt");
  std::ifstream fin4("internal/metrics/testProgs/cpp/code2.txt");

  MyCppAntlr cppA1 = MyCppAntlr(fin3);
  MyCppAntlr cppA2 = MyCppAntlr(fin4);

 // std::vector <std::string> str_tokens1 = cppA1.getTokensNames();
 // std::vector <std::string> str_tokens2 = cppA2.getTokensNames();

  std::vector <std::pair <std::string, int> > str_int_tokens2 = cppA2.getTokensNamesWithPosition();
  std::vector <std::pair <std::string, int> > str_int_tokens1 = cppA1.getTokensNamesWithPosition();

  for (int i = 0; i < str_int_tokens1.size(); i++){
      std::cout << str_int_tokens1[i].first << " " << str_int_tokens1[i].second << std::endl;
  }

  //PythonAntlr pyA1 = PythonAntlr(fin3);
  //PythonAntlr pyA2 = PythonAntlr(fin4);

  foundSame.setData2(str_int_tokens1, str_int_tokens2);
  std::pair <std::string, std::string> res = foundSame.getTexts2();

  std::vector<int> tokens1 = cppA1.getTokensTypes();
  std::vector<int> tokens2 = cppA2.getTokensTypes();



//  LevDistTokenMetric lev;
//  WShinglingTokenMetric wsh;
//  lev.setData(tokens1, tokens2);
//  wsh.setData(tokens1, tokens2);
//
//  std::cout << "Tokens1:" << std::endl;
//  for (int token : tokens1) {
//    std::cout << token << " ";
//  }
//  std::cout << std::endl;
//
//  std::cout << "Tokens2:" << std::endl;
//  for (int token : tokens2) {
//      std::cout << token << " ";
//  }
//  std::cout << std::endl;
//
//  std::cout << lev.getMetric() << std::endl << wsh.getMetric() << std::endl;
  fin3.close();
  fin4.close();
  return 0;
}
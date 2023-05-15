#include <iostream>

#include "PythonAntlr.h"
#include "MyCppAntlr.h"
#include "TokenMetricLib.h"

int main(int argc, const char* argv[]) {
  //   ifstream ins("/home/denis/2023_1_DDT/antlr/test.py");
  std::ifstream fin1("internal/metrics/testProgs/cpp/code1.txt");
  std::ifstream fin2("internal/metrics/testProgs/cpp/code2.txt");

  MyCppAntlr cppA1 = MyCppAntlr(fin1);
  MyCppAntlr cppA2 = MyCppAntlr(fin2);

  std::vector<int> tokens1 = cppA1.getTokensTypes();
  std::vector<int> tokens2 = cppA2.getTokensTypes();

  LevDistTokenMetric lev;
  lev.setData(tokens1, tokens2);

  std::cout << "Tokens1:" << std::endl;
  for (int token : tokens1) {
    std::cout << token << " ";
  }
  std::cout << std::endl;

  std::cout << "Tokens2:" << std::endl;
  for (int token : tokens2) {
      std::cout << token << " ";
  }
  std::cout << std::endl;


  std::cout << lev.getMetric() << std::endl;

  return 0;
}
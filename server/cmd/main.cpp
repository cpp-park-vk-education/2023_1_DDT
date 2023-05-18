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
  WShinglingTokenMetric wsh;
  lev.setData(tokens1, tokens2);
  wsh.setData(tokens1, tokens2);

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

  std::cout << lev.getMetric() << std::endl << wsh.getMetric() << std::endl;

  fin1.close();
  fin2.close();

  std::vector <int> tokens3 = {9, 45, 132, 85, 86, 89, 78, 45, 132, 128, 45, 132, 101, 1,
                               128, 132, 127, 132, 103, 103, 132, 128, 84, 85, 132, 115, 1, 86,
                               89, 43, 85, 132, 97, 1, 86, 132, 120, 128, 132, 113, 1, 128, 90,
                               132, 127, 132, 102, 102, 132, 128, 59, 1, 128, 90, -1};

  wsh.setData(tokens3, tokens3);
  std::cout << wsh.getMetric() << std::endl;
  return 0;
}
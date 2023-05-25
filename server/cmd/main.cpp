#include <iostream>

#include "PythonAntlr.h"
#include "MyCppAntlr.h"
#include "TokenMetricLib.h"
#include "TextMetricsLib.h"
#include "DiffLib.h"

int main(int argc, const char* argv[]) {
  FoundSame foundSame;

  std::ifstream fin3("internal/metrics/testProgs/cpp/code1.txt");
  std::ifstream fin4("internal/metrics/testProgs/cpp/code4.txt");

  //PythonAntlr pyA1 = PythonAntlr(fin3);
  //PythonAntlr pyA2 = PythonAntlr(fin4);

  MyCppAntlr cppA1 = MyCppAntlr(fin3);
  MyCppAntlr cppA2 = MyCppAntlr(fin4);

  std::vector <std::pair <std::string, int> > str_int_tokens2 = cppA2.getTokensNamesWithPosition();
  std::vector <std::pair <std::string, int> > str_int_tokens1 = cppA1.getTokensNamesWithPosition();


  foundSame.setData(str_int_tokens1, str_int_tokens2);
  std::pair <std::string, std::string> res = foundSame.getTexts();

  std::ofstream out1("internal/metrics/testProgs/output/out1.txt");
  std::ofstream out2("internal/metrics/testProgs/output/out2.txt");

  out1 << res.first;
  out2 << res.second;

  out1.close();
  out2.close();
  fin3.close();
  fin4.close();
  return 0;
}
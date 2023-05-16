#include <iostream>

#include "PythonAntlr.h"
#include "MyCppAntlr.h"

int main(int argc, const char* argv[]) {
  //   ifstream ins("/home/denis/2023_1_DDT/antlr/test.py");
  std::ifstream ins(
      "/home/denis/2023_1_DDT/server/pkg/antlr/testprogs/cpp/test.cpp");

  MyCppAntlr pA = MyCppAntlr(ins);

  std::vector<int> tokens = pA.getTokensTypes();

  std::cout << "Tokens:" << std::endl;
  for (int token : tokens) {
    std::cout << token << std::endl;
  }

  // std::cout << pA.getTreeString() << std::endl;

  return 0;
}
#include <iostream>

#include "PythonAntlr.h"

int main(int argc, const char* argv[]) {
  //   ifstream ins("/home/denis/2023_1_DDT/antlr/test.py");
  std::ifstream ins(
      "/home/denis/2023_1_DDT/server/pkg/antlr/testprogs/python/test.py");

  PythonAntlr pA = PythonAntlr(ins);

  std::vector<std::string> tokens = pA.getTokensArray();

  std::cout << "Tokens:" << std::endl;
  for (std::string token : tokens) {
    std::cout << token << std::endl;
  }

  std::cout << pA.getTreeString() << std::endl;
  std::cout << "test" << std::endl;

  return 0;
}
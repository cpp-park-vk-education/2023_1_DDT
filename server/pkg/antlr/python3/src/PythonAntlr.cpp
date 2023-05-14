#include "PythonAntlr.h"

#include <iostream>

PythonAntlr::PythonAntlr(std::ifstream& in) {
  input_ptr = std::make_unique<antlr4::ANTLRInputStream>(in);
  lexer_ptr = std::make_unique<antlrcpptest::Python3Lexer>(&(*input_ptr));
  tokenStream_ptr = std::make_unique<antlr4::CommonTokenStream>(&(*lexer_ptr));
  parser_ptr = std::make_unique<antlrcpptest::Python3Parser>(&(*tokenStream_ptr));
}

std::vector<std::string> PythonAntlr::getTokensArray() {
  tokenStream_ptr->fill();
  std::vector<std::string> ans(tokenStream_ptr->size());

  int i = 0;
  for (antlr4::Token* token : tokenStream_ptr->getTokens()) {
    ans[i] = token->toString();
    i++;
  }

  return ans;
}

std::string PythonAntlr::getTokensString() {
  tokenStream_ptr->fill();
  std::string res;

  for (antlr4::Token* token : tokenStream_ptr->getTokens()) {
    res += token->toString()+" ";
  }

  return res;
}

std::string PythonAntlr::getTreeString() {
  auto tree = parser_ptr->file_input();
  return tree->toStringTree(&(*parser_ptr));
}

std::pair<std::string, std::string> PythonAntlr::getTokensAndTree() {
  std::string tokens = getTokensString();
  std::string astTree = getTreeString();
  return std::make_pair(tokens, astTree);
}
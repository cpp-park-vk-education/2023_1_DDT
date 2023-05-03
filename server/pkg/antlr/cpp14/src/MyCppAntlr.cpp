#include "MyCppAntlr.h"

#include <iostream>

MyCppAntlr::MyCppAntlr(std::unique_ptr<antlr4::ANTLRInputStream> input,
                   std::unique_ptr<antlr4::CommonTokenStream> tokenStream,
                   std::unique_ptr<antlrcpptest::CPP14Lexer> lexer,
                   std::unique_ptr<antlrcpptest::CPP14Parser> parser)
    : input_ptr(std::move(input)),
      tokenStream_ptr(std::move(tokenStream)),
      lexer_ptr(std::move(lexer)),
      parser_ptr(std::move(parser)) {}

std::unique_ptr<MyCppAntlr> MyCppAntlr::init(std::ifstream& in) {
  auto input = std::make_unique<antlr4::ANTLRInputStream>(in);
  auto lex = std::make_unique<antlrcpptest::CPP14Lexer>(&(*input));
  auto tok = std::make_unique<antlr4::CommonTokenStream>(&(*lex));
  auto parser = std::make_unique<antlrcpptest::CPP14Parser>(&(*tok));
  auto a = std::make_unique<MyCppAntlr>(
      MyCppAntlr(std::move(input),std::move(tok), std::move(lex),
               std::move(parser)));
  return std::move(a);
}

std::vector<std::string> MyCppAntlr::getTokens() {
  tokenStream_ptr->fill();
  std::vector<std::string> ans(tokenStream_ptr->size());

  int i = 0;
  for (antlr4::Token* token : tokenStream_ptr->getTokens()) {
    ans[i] = token->toString();
    i++;
  }

  return ans;
}

std::string MyCppAntlr::getTreeString() {
  auto tree = parser_ptr->translationUnit();
  return tree->toStringTree(&(*parser_ptr));
}
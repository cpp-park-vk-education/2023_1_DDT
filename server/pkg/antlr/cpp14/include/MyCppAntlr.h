#pragma once

#include <fstream>
#include <memory>
#include <vector>

#include "CPP14Lexer.h"
#include "CPP14Parser.h"
#include "IAntlrWrapper.h"
#include "antlr4-runtime.h"

class MyCppAntlr:IAntlrWrapper {
 private:
  std::unique_ptr<antlrcpptest::CPP14Lexer> lexer_ptr;
  std::unique_ptr<antlrcpptest::CPP14Parser> parser_ptr;
  std::unique_ptr<antlr4::ANTLRInputStream> input_ptr;
  std::unique_ptr<antlr4::CommonTokenStream> tokenStream_ptr;

 public:
  MyCppAntlr(std::unique_ptr<antlr4::ANTLRInputStream> input,
             std::unique_ptr<antlr4::CommonTokenStream> tokenStream,
             std::unique_ptr<antlrcpptest::CPP14Lexer> lexer,
             std::unique_ptr<antlrcpptest::CPP14Parser> parser);

  static std::unique_ptr<MyCppAntlr> init(std::ifstream &in);

  std::vector<std::string> getTokens() override;

  // antlr4::tree::ParseTree *getTree();
  std::string getTreeString() override;
};

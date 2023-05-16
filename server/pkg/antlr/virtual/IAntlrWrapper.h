#pragma once

#include <utility>
#include <vector>

#include "antlr4-runtime.h"

class IAntlrWrapper {
 public:
  virtual ~IAntlrWrapper() = default;
  virtual std::vector<antlr4::Token*> getTokens() = 0;
  virtual std::vector<int> getTokensTypes() = 0;
  virtual std::pair<std::string, std::string> getTokensAndTree() = 0;
  virtual std::string getTokensString() = 0;
  virtual std::string getTreeString() = 0;
};

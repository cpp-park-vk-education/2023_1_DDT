#pragma once

#include <vector>

class IAntlrWrapper {
 public:
  virtual std::vector<std::string> getTokens() = 0;
  virtual std::string getTreeString() = 0;
};

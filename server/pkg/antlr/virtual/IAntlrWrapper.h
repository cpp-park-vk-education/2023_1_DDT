#pragma once

#include <vector>
#include <utility>

class IAntlrWrapper {
 public:
  virtual ~IAntlrWrapper() = default;
  virtual std::vector<std::string> getTokensArray() = 0;
  virtual std::pair<std::string, std::string> getTokensAndTree()=0;
  virtual std::string getTokensString() = 0;
  virtual std::string getTreeString() = 0;
};

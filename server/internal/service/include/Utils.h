#pragma once

#include <vector>
#include <string>

class Utils {
 public:
  static std::string convertIntArrayIntoString(std::vector<int>& arr);
  static std::vector<int> convertStringIntoIntArray(const std::string& str);
};

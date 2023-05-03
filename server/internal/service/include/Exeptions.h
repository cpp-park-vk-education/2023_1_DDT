#pragma once

class ValidateExeption : public std::exception {
  std::string _msg;

 public:
  ValidateExeption(const std::string& msg) : _msg(msg) {}
  virtual const char* what() const noexcept override { return _msg.c_str(); }
};
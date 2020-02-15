#ifndef __Exceptions__
#define __Exceptions__

class DefaultException: public std::exception {
private:
    std::string message_;
public:
    DefaultException(const std::string& message) : message_(message) {}
    virtual const char* what() const throw() {
        return message_.c_str();
    }
};


class AST_Exception: public DefaultException {
public:
  AST_Exception(const std::string& message):DefaultException(message) {}
};


class Semantic_Exception: public DefaultException {
public:
  Semantic_Exception(const std::string& message):DefaultException(message) {}
};

class ICR_Exception: public DefaultException {
public:
  ICR_Exception(const std::string& message):DefaultException(message) {}
};

class ASM_Exception: public DefaultException {
public:
  ASM_Exception(const std::string& message):DefaultException(message) {}
};

namespace MC{
  class MCC_Exception: public DefaultException {
  public:
    MCC_Exception(const std::string& message):DefaultException(message)  {}
  };
}

#endif

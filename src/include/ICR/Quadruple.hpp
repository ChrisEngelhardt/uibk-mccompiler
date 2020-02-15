#ifndef UNTITLED_QUADRUPLE_H
#define UNTITLED_QUADRUPLE_H

#include <iostream>
#include <memory>

namespace MC{
  struct Quadruple{
  public:

    enum OperationType{
      copyI, copyF, copyS, declarationArray, copyToArrayI, copyToArrayF, copyToArrayS,
        copyFromArrayI, copyFromArrayF, copyFromArrayS, unaryI, unaryF, binaryI, binaryF,
        ucJump, cJump, label, labelF, parameter, parameterF, pCall, pCallF, rtrn, rtrnF
    };

    OperationType ot;
    std::string arg1;
    std::string arg2;
    std::string result;
    std::string op = "";

    Quadruple(OperationType ot, std::string arg1, std::string arg2, std::string result) : ot(ot), arg1(arg1), arg2(arg2), result(result) { }
    Quadruple(OperationType ot, std::string arg1, std::string result) : ot(ot), arg1(arg1), arg2(""), result(result) { }
    Quadruple(OperationType ot, std::string arg1) : ot(ot), arg1(arg1), arg2(""), result("") { }

  };

  typedef std::shared_ptr<Quadruple> Quadruple_p;
}

#endif

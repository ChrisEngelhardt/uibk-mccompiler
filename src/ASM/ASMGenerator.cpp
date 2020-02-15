#include "../include/ASM/ASMGenerator.hpp"

#include "../app/include/StringUtils.hpp"
#include "include/mcc/Exceptions.hpp"

using namespace MC;

std::ostream& ASMGenerator::generate(std::vector<Quadruple_p> *icr, std::ostream&, std::ostream& asmOs, std::string name, const std::string function){
  icr = icr;

  //Generate header
  if (function == ""){
    asmOs << "\t.file \"" << basenameMC(name) << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << ENTRYPOINT << "\n";
    asmOs << "\t.type " << ENTRYPOINT << ", @function\n";
  }


  //Generate code
  auto byteCounterPerMethod = ASMGenerator::calculateByteCounterPerMethod(icr);
  std::map<std::string, int> s;
  int stackOffsetCounter = 0;

  int parameterCounter = 0;

  std::ostringstream floatStringHolderOS;
  int floatStringCounter = 0;

  std::string currentFunction = "";

  for (auto p : *icr) {
    if (function != ""){
      if (p->ot == Quadruple::OperationType::labelF){
        currentFunction = p->arg1;
      }
      if (currentFunction != function){
        continue;
      }
    }

    switch (p->ot) {
      case Quadruple::OperationType::copyI:
      /* FALLTHRU */
      case Quadruple::OperationType::copyF:
      /* FALLTHRU */
      case Quadruple::OperationType::copyS:
        ASMGenerator::copyExpression(s,stackOffsetCounter,p,floatStringCounter,floatStringHolderOS,asmOs);
        break;
      case Quadruple::OperationType::declarationArray:
        stackOffsetCounter+=(std::stoi(p->arg1)+1);
        s[p->result] = stackOffsetCounter-1;
        execExpression(stackOffsetCounter-2, I_LEAL, asmOs);
        moveToStackExpression(stackOffsetCounter-1, asmOs);
        break;
      case Quadruple::OperationType::copyFromArrayI:
      /* FALLTHRU */
      case Quadruple::OperationType::copyFromArrayF:
      /* FALLTHRU */
      case Quadruple::OperationType::copyFromArrayS:
        if(s.count(p->result) == 0){
          s[p->result] = stackOffsetCounter;
          stackOffsetCounter++;
        }
        asmOs << "\t" <<I_MOVE<<"\t-"<< (s[p->arg2]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<"), "<<EDX_REG<<"\n";
        execExpression(s[p->arg1], I_MOVE, asmOs);
        asmOs << "\t" <<I_LEAL<<"\t0("<< ACC_REG<<","<<EDX_REG<<",4), "<<ECX_REG<<"\n";
        asmOs << "\t" <<I_MOVE<<"\t("<< ECX_REG<<"),"<<ACC_REG<<"\n";
        moveToStackExpression(s[p->result],asmOs);
        break;
      case Quadruple::OperationType::copyToArrayI:
      /* FALLTHRU */
      case Quadruple::OperationType::copyToArrayF:
      /* FALLTHRU */
      case Quadruple::OperationType::copyToArrayS:
        asmOs << "\t" <<I_MOVE<<"\t-"<< (s[p->arg2]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<"), "<<EDX_REG<<"\n";
        execExpression(s[p->result], I_MOVE, asmOs);
        asmOs << "\t" <<I_LEAL<<"\t0("<< ACC_REG<<","<<EDX_REG<<",4), "<<ECX_REG<<"\n";
        execExpression(s[p->arg1], I_MOVE, asmOs);
        asmOs << "\t" <<I_MOVE<<"\t"<< ACC_REG<<", ("<<ECX_REG<<")\n";
        break;
      case Quadruple::OperationType::binaryI:
      /* FALLTHRU */
      case Quadruple::OperationType::binaryF:
        ASMGenerator::binaryExpression(s,stackOffsetCounter,p,asmOs);
        break;
      case Quadruple::OperationType::label:
        asmOs << "." << p->arg1 << ":\n";
        break;
      case Quadruple::OperationType::labelF:
        parameterCounter=0;
        s.clear();
        stackOffsetCounter=0;
        asmOs << (p->arg1 == ENTRYPOINT ? "" : "") << p->arg1 << ":\n";
        asmOs << "\t"<<I_PUSH<<"\t"<<DATA_STACK_REG<<"\n";
        asmOs << "\t"<<I_MOVE<<"\t"<<STACK_POINTER<<", "<<DATA_STACK_REG<<"\n";
        if (byteCounterPerMethod.count(p->arg1) == 0){
          throw(ASM_Exception("Failed to convert to asm"));
        }
        asmOs << "\t"<<I_SUB<<"\t$"<<byteCounterPerMethod[p->arg1]<<", "<<STACK_POINTER<<"\n";
        break;
      case Quadruple::OperationType::ucJump:
        asmOs << "\t"<<I_JUMP<<"\t." << p->arg1 << "\n";
        break;
      case Quadruple::OperationType::parameter:
        asmOs << "\t"<<I_PUSH<<"\t-"<< (s[p->arg1]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";
        break;
      case Quadruple::OperationType::parameterF:
          parameterFExpression(s,stackOffsetCounter, p, parameterCounter++,asmOs);
          break;
      case Quadruple::OperationType::pCall:
        ASMGenerator::pCallExpression(s,stackOffsetCounter,p,asmOs);
        break;
      case Quadruple::OperationType::pCallF:
          ASMGenerator::pCallExpression(s,stackOffsetCounter,p,asmOs,true);
          break;
      case Quadruple::OperationType::unaryI:
      /* FALLTHRU */
      case Quadruple::OperationType::unaryF:
        ASMGenerator::unaryExpression(s,stackOffsetCounter,p,asmOs);
        break;
      case Quadruple::OperationType::cJump:
        asmOs << "\t"<<I_CMP<<"\t$1, -"<< (s[p->arg1]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";
        asmOs << "\t"<<I_CJUMP<<"\t."<< p->result <<"\n";
        break;

      case Quadruple::OperationType::rtrn:
        if (p->arg1 != ""){
          execExpression(s[p->arg1], I_MOVE, asmOs);
        }
        asmOs << "\tleave\n";
        asmOs << "\tret\n";
        break;
      case Quadruple::OperationType::rtrnF:
        asmOs << "\t" <<I_FLDS<<"\t-"<< (s[p->arg1]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";
        asmOs << "\tleave\n";
        asmOs << "\tret\n";
        break;
    }
  }
  asmOs<<floatStringHolderOS.str();

  return asmOs;
}


std::map<std::string, int> ASMGenerator::calculateByteCounterPerMethod(std::vector<Quadruple_p> *icr){
  std::map<std::string, int> byteCounterPerMethod;
  std::map<std::string, int> byteCounterPerVariable;
  std::string currentFunction = "";
  int byteCounter = 0;

  for (auto p : *icr) {
    switch (p->ot) {
      case Quadruple::OperationType::labelF:
        if (currentFunction != ""){
          byteCounterPerMethod[currentFunction] = byteCounter;
          byteCounter = 0;
          byteCounterPerVariable.clear();
        }
        currentFunction = p->arg1;
        break;
      case Quadruple::OperationType::parameterF:
      /* FALLTHRU */
      case Quadruple::OperationType::pCall:
      /* FALLTHRU */
      case Quadruple::OperationType::pCallF:
      /* FALLTHRU */
      case Quadruple::OperationType::binaryI:
      /* FALLTHRU */
      case Quadruple::OperationType::binaryF:
      /* FALLTHRU */
      case Quadruple::OperationType::unaryI:
      /* FALLTHRU */
      case Quadruple::OperationType::unaryF:
      /* FALLTHRU */
      case Quadruple::OperationType::copyI:
      /* FALLTHRU */
      case Quadruple::OperationType::copyF:
      /* FALLTHRU */
      case Quadruple::OperationType::copyS:
        if(byteCounterPerVariable.count(p->result) == 0){
          byteCounterPerVariable[p->result] = INT_SIZE;
          byteCounter+=INT_SIZE;
        }
        break;
      case Quadruple::OperationType::declarationArray:
        if(byteCounterPerVariable.count(p->result) == 0){
          int totalArraySize = (std::stoi(p->arg1)+1) * INT_SIZE;
          byteCounterPerVariable[p->result] = totalArraySize;
          byteCounter+=totalArraySize;
        }
        break;
      default:
        break;
    }
  }
  byteCounterPerMethod[currentFunction] = byteCounter;
  return byteCounterPerMethod;
}

std::ostream& ASMGenerator::execExpression(int offset, std::string op, std::ostream& asmOs){
  asmOs << "\t" <<op<<"\t-"<< (offset+1)*INT_SIZE<<"("<<DATA_STACK_REG<<"), "<<ACC_REG<<"\n";
  return asmOs;
}

std::ostream& ASMGenerator::parameterFExpression(std::map<std::string, int>& variableMap, int& stackOffsetCounter, Quadruple_p p, int parameterCounter, std::ostream& asmOs){
  if(variableMap.count(p->result) == 0){
    variableMap[p->result] = stackOffsetCounter;
    stackOffsetCounter++;
  }
  asmOs << "\t" <<I_MOVE<<"\t"<< (parameterCounter+2)*INT_SIZE<<"("<<DATA_STACK_REG<<"), "<<ACC_REG<<"\n";
  moveToStackExpression(variableMap[p->result], asmOs);
  return asmOs;
}

std::ostream& ASMGenerator::pCallExpression(std::map<std::string, int>& variableMap, int& stackOffsetCounter, Quadruple_p p, std::ostream& asmOs, bool isFloat){
  if(variableMap.count(p->result) == 0){
    variableMap[p->result] = stackOffsetCounter;
    stackOffsetCounter++;
  }
  asmOs << "\t" <<I_CALL<<"\t" << p->arg1 << "\n";
  if(isFloat){
    asmOs << "\t" <<I_FSTPS<<"\t-"<< (variableMap[p->result]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";
  } else {
    moveToStackExpression(variableMap[p->result], asmOs);
  }
  return asmOs;
}

std::ostream& ASMGenerator::moveToStackExpression(int offset, std::ostream& asmOs){
  asmOs << "\t"<<I_MOVE<<"\t"<< ACC_REG <<", -"<< (offset+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";
  return asmOs;
}


std::ostream& ASMGenerator::copyExpression(std::map<std::string, int>& variableMap, int& stackOffsetCounter, Quadruple_p p, int& floatStringCounter, std::ostream& floatStringHolderOS, std::ostream& asmOs){
  if(variableMap.count(p->result) == 0){
    variableMap[p->result] = stackOffsetCounter;
    stackOffsetCounter++;
  }

  if (p->arg1.at(0) == 't'){
    execExpression(variableMap[p->arg1], I_MOVE, asmOs);
    moveToStackExpression(variableMap[p->result], asmOs);
  } else {
    switch (p->ot) {
      case Quadruple::OperationType::copyI:
        asmOs << "\t"<<I_MOVE<<"\t$"<< p->arg1 <<", -"<< (variableMap[p->result]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";
        break;
      case Quadruple::OperationType::copyF:
        floatStringHolderOS<<".df"<<floatStringCounter<<":\n";
        floatStringHolderOS<<"\t"<<I_FLOAT<<"\t"<<p->arg1<<"\n";

        asmOs << "\t"<<I_MOVE<<"\t.df"<< floatStringCounter <<", "<< ACC_REG <<"\n";
        moveToStackExpression(variableMap[p->result], asmOs);
        floatStringCounter++;
        break;
      case Quadruple::OperationType::copyS:
        floatStringHolderOS<<".df"<<floatStringCounter<<":\n";
        floatStringHolderOS<<"\t"<<I_STRING<<"\t"<<p->arg1<<"\n";

        asmOs << "\t"<<I_MOVE<<"\t$.df"<< floatStringCounter <<", -"<< (variableMap[p->result]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";

        floatStringCounter++;
        break;
      default:
        throw(ASM_Exception("Unknown copy expression"));
        break;
    }
  }
  return asmOs;
}

std::ostream& ASMGenerator::floatCalculusExpression(std::string op,std::map<std::string, int>& variableMap, Quadruple_p p, std::ostream& asmOs){
  asmOs << "\t" <<I_FLDS<<"\t-"<< (variableMap[p->arg1]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";
  asmOs << "\t" <<op<<"\t-"<< (variableMap[p->arg2]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";
  asmOs << "\t" <<I_FSTPS<<"\t-"<< (variableMap[p->result]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";
  return asmOs;
}

std::ostream& ASMGenerator::floatBoolExpression(std::string op,std::map<std::string, int>& variableMap, Quadruple_p p, std::ostream& asmOs){
  asmOs << "\t" <<I_FLDS<<"\t-"<< (variableMap[p->arg2]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";
  asmOs << "\t" <<I_FLDS<<"\t-"<< (variableMap[p->arg1]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";
  asmOs << "\t" <<I_FCOMIP<<"\t%st(1), %st\n";
  asmOs << "\t" <<I_FSTP<<"\t%st\n";
  asmOs << "\t" << op << "\t" << ACC_BYTE_0_REG<< "\n";
  asmOs << "\t" << I_MOVZBL << "\t" << ACC_BYTE_0_REG << ", " << ACC_REG << "\n";
  moveToStackExpression(variableMap[p->result], asmOs);
  return asmOs;
}

std::ostream& ASMGenerator::binaryExpression(std::map<std::string, int>& variableMap, int& stackOffsetCounter, Quadruple_p p, std::ostream& asmOs){
  if(variableMap.count(p->result) == 0){
    variableMap[p->result] = stackOffsetCounter;
    stackOffsetCounter++;
  }

  switch (p->ot) {
    case Quadruple::OperationType::binaryI:
      execExpression(variableMap[p->arg1], I_MOVE, asmOs);
      if(p->op == "+"){
        execExpression(variableMap[p->arg2], I_ADD, asmOs);
      } else if(p->op == "-"){
        execExpression(variableMap[p->arg2], I_SUB, asmOs);
      } else if(p->op == "*"){
        execExpression(variableMap[p->arg2], I_MUL, asmOs);
      } else if(p->op == "/"){
        asmOs << "\t" <<I_CONV_SLONG_TO_SDOUBLE<<"\n";
        asmOs << "\t" <<I_DIV<<"\t-"<< (variableMap[p->arg2]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";
      } else if(p->op == "=="){
        execExpression(variableMap[p->arg2], I_CMP, asmOs);
        binaryBoolExpression(I_SETE,asmOs);
      } else if(p->op == "!="){
        execExpression(variableMap[p->arg2], I_CMP, asmOs);
        binaryBoolExpression(I_SETNE,asmOs);
      } else if(p->op == "<"){
        execExpression(variableMap[p->arg2], I_CMP, asmOs);
        binaryBoolExpression(I_SETL,asmOs);
      } else if(p->op == ">"){
        execExpression(variableMap[p->arg2], I_CMP, asmOs);
        binaryBoolExpression(I_SETG,asmOs);
      } else if(p->op == "<="){
        execExpression(variableMap[p->arg2], I_CMP, asmOs);
        binaryBoolExpression(I_SETLE,asmOs);
      } else if(p->op == ">="){
        execExpression(variableMap[p->arg2], I_CMP, asmOs);
        binaryBoolExpression(I_SETGE,asmOs);
      } else if(p->op == "&&"){
        execExpression(variableMap[p->arg2], I_AND, asmOs);
      } else if(p->op == "||"){
        execExpression(variableMap[p->arg2], I_OR, asmOs);
      } else {
        throw(ASM_Exception("Unknown unary expression"));
      }
      moveToStackExpression(variableMap[p->result], asmOs);
      break;
    case Quadruple::OperationType::binaryF:
      if(p->op == "+"){
        floatCalculusExpression(I_FADDS,variableMap,p,asmOs);
      } else if(p->op == "-"){
        floatCalculusExpression(I_FSUBS,variableMap,p,asmOs);
      } else if(p->op == "*"){
        floatCalculusExpression(I_FMULS,variableMap,p,asmOs);
      } else if(p->op == "/"){
        floatCalculusExpression(I_FDIVS,variableMap,p,asmOs);
      } else if(p->op == "=="){
        execExpression(variableMap[p->arg1], I_MOVE, asmOs);
        execExpression(variableMap[p->arg2], I_CMP, asmOs);
        binaryBoolExpression(I_SETE,asmOs);
        moveToStackExpression(variableMap[p->result], asmOs);
      } else if(p->op == "!="){
        execExpression(variableMap[p->arg1], I_MOVE, asmOs);
        execExpression(variableMap[p->arg2], I_CMP, asmOs);
        binaryBoolExpression(I_SETNE,asmOs);
        moveToStackExpression(variableMap[p->result], asmOs);
      } else if(p->op == "<"){
        floatBoolExpression(I_SETB,variableMap,p,asmOs);
      } else if(p->op == ">"){
        floatBoolExpression(I_SETA,variableMap,p,asmOs);
      } else if(p->op == "<="){
        floatBoolExpression(I_SETBE,variableMap,p,asmOs);
      } else if(p->op == ">="){
        floatBoolExpression(I_SETAE,variableMap,p,asmOs);
      } else {
        throw(ASM_Exception("Unknown unary expression"));
      }

      break;
    default:
      throw(ASM_Exception("Unknown copy expression"));
      break;
  }

  return asmOs;
}

std::ostream& ASMGenerator::binaryBoolExpression(std::string op, std::ostream& asmOs){
  asmOs << "\t" << op << "\t" << ACC_BYTE_0_REG << "\n";
  asmOs << "\t" << I_MOVZBL << "\t" << ACC_BYTE_0_REG << ", " << ACC_REG << "\n";
  return asmOs;
}


std::ostream& ASMGenerator::unaryExpression(std::map<std::string, int>& variableMap, int& stackOffsetCounter, Quadruple_p p, std::ostream& asmOs){
  if(variableMap.count(p->result) == 0){
    variableMap[p->result] = stackOffsetCounter;
    stackOffsetCounter++;
  }

  switch (p->ot) {
    case Quadruple::OperationType::unaryI:
      if(p->op == "-"){
        execExpression(variableMap[p->arg1], I_MOVE, asmOs);
        asmOs << "\t" <<I_MUL<<"\t$-1, "<<ACC_REG<<"\n";
        moveToStackExpression(variableMap[p->result], asmOs);
      } else if(p->op == "!"){
        execExpression(variableMap[p->arg1], I_MOVE, asmOs);
        asmOs << "\t" <<I_XORL<<"\t$1, "<<ACC_REG<<"\n";
        moveToStackExpression(variableMap[p->result], asmOs);
      }else {
        throw(ASM_Exception("Unknown unary expression"));
      }
      break;
    case Quadruple::OperationType::unaryF:
      if(p->op == "-"){
        asmOs << "\t" <<I_FLDS<<"\t-"<< (variableMap[p->arg1]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";
        asmOs << "\t" <<I_FCHS<<"\n";
        asmOs << "\t" <<I_FSTPS<<"\t-"<< (variableMap[p->result]+1)*INT_SIZE<<"("<<DATA_STACK_REG<<")\n";
      } else {
        throw(ASM_Exception("Unknown unary expression"));
      }
      break;
    default:
      throw(ASM_Exception("Unknown copy expression"));
      break;
  }
  return asmOs;
}

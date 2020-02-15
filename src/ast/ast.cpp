#include "../include/ast/AST.hpp"

#include "include/ast/DeclarationStmtAST.hpp"
#include "include/SymbolTable/SymbolTable.hpp"

using namespace MC;

bool MC::operator==(const VariableTypeArray& lhs, const VariableTypeArray& rhs){
    return lhs.varType == rhs.varType && lhs.arraySize == rhs.arraySize;
}

AST::AST(ASTTypes astType):astType(astType){

}

AST::AST(ASTTypes astType, int lineNumber):astType(astType),lineNumber(lineNumber){

}

AST::~AST(){

}

ASTTypes AST::getAstType(){
  return astType;
}

std::string AST::getAstTypeAsString() const{
  return astTypeString;
}

std::string AST::getAsString() const{
  return "";
}

void AST::setAstTypeString(std::string astTypeString){
  this->astTypeString = astTypeString;
}


std::ostream& operator<<(std::ostream &os, const  AST& n){
  os <<n.getAstTypeAsString()<<std::endl;
  return os;
}

int AST::getLineNumber(){
  return lineNumber;
}

void AST::generateDOT(DOTTree_p){}

void AST::preOrder(std::function<void(AST*)>){}

void AST::postOrder(std::function<void(AST*)>, bool){}

VariableType AST::getVariableTypeFromString(std::string variableType){
  if(variableType == "int"){
    return VariableType::intType;
  }
  if(variableType == "float"){
    return VariableType::floatType;
  }
  if(variableType == "string"){
    return VariableType::stringType;
  }
  if(variableType == "bool"){
    return VariableType::boolType;
  }
  return VariableType::voidType;
}

std::string AST::getVariableTypeAsString(VariableType variableType){
  if(variableType == VariableType::intType){
    return "int";
  }
  if(variableType == VariableType::floatType){
    return "float";
  }
  if(variableType == VariableType::stringType){
    return "string";
  }
  if(variableType == VariableType::boolType){
    return "bool";
  }
  if(variableType == VariableType::voidType){
    return "void";
  }
  return "undefined";
}

std::string AST::getVariableTypeAsString(VariableTypeArray variableType){
  if(variableType.arraySize == -1){
    return AST::getVariableTypeAsString(variableType.varType);
  } else {
    return AST::getVariableTypeAsString(variableType.varType)+"["+std::to_string(variableType.arraySize)+"]";
  }
}

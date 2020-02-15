#include "../include/ast/ExpressionAST.hpp"

#include "../include/SymbolTable/SymbolTable.hpp"

using namespace MC;

ExpressionAST::ExpressionAST(ExpressionAST::Type expressionType, int lineNumber):AST(expression, lineNumber),dataType(undefined),expressionType(expressionType){
  setAstTypeString("Expression");
}


ExpressionAST::~ExpressionAST(){

}

ExpressionAST::Type ExpressionAST::getExpressionType(){
  return expressionType;
}


void ExpressionAST::evaluateType(std::ostream&, SymbolTable &){}


VariableType ExpressionAST::getDataType(){
  return dataType;
}

#include "../include/ast/IntLiteralAST.hpp"

using namespace MC;

IntLiteralAST::IntLiteralAST(long variable, int lineNumber):LiteralAST(intType, lineNumber),variable(variable){
  setAstTypeString("IntLiteralAST: "+std::to_string(variable));
}

IntLiteralAST::~IntLiteralAST(){

}

long IntLiteralAST::getVariable() const{
  return variable;
}

std::string IntLiteralAST::getAsString() const{
  return std::to_string(variable);
}

void IntLiteralAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();

  t->setLabel(getAsString());
  dot->addSubtree(t);
}

void IntLiteralAST::preOrder(std::function<void(AST*)> f){
  f(this);
}

void IntLiteralAST::postOrder(std::function<void(AST*)> f, bool){
  f(this);
}

void IntLiteralAST::evaluateType(std::ostream& os, SymbolTable &){
  dataType = VariableType::intType;
  os<<"Set the data type of the int literal "<<getLineNumber()<<" to int"<<std::endl;

}

void IntLiteralAST::generateICR(std::ostream&){
  //Create new temporary
  uniqueName = ICRepresentation::instance()->getUniqueVariableName();
  auto s = std::make_shared<Quadruple>(Quadruple::OperationType::copyI, std::to_string(variable), uniqueName);
  ICRepresentation::instance()->insert(s);
}

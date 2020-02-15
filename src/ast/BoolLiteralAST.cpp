#include "../include/ast/BoolLiteralAST.hpp"

using namespace MC;

BoolLiteralAST::BoolLiteralAST(bool variable, int lineNumber):LiteralAST(boolType, lineNumber),variable(variable){
  setAstTypeString("BoolLiteral: " + getAsString());
}

BoolLiteralAST::~BoolLiteralAST(){

}

std::string BoolLiteralAST::getAsString() const{
  return (variable ? "true" : "false");
}

void BoolLiteralAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();


  t->setLabel(getAsString());
  dot->addSubtree(t);
}

void BoolLiteralAST::preOrder(std::function<void(AST*)> f){
  f(this);
}

void BoolLiteralAST::postOrder(std::function<void(AST*)> f, bool){
  f(this);
}

void BoolLiteralAST::evaluateType(std::ostream& os, SymbolTable &){
  dataType = VariableType::boolType;
  os<<"Set the data type of the bool literal "<<getLineNumber()<<" to bool"<<std::endl;
}

void BoolLiteralAST::generateICR(std::ostream&){
  //Create new temporary
  uniqueName = ICRepresentation::instance()->getUniqueVariableName();
  auto s = std::make_shared<Quadruple>(Quadruple::OperationType::copyI, variable ? "1" : "0", uniqueName);
  ICRepresentation::instance()->insert(s);
}

#include "../include/ast/FloatLiteralAST.hpp"

using namespace MC;

FloatLiteralAST::FloatLiteralAST(double variable, int lineNumber):LiteralAST(floatType, lineNumber),variable(variable){
  setAstTypeString("FloatLiteralAST: "+std::to_string(variable));
}

FloatLiteralAST::~FloatLiteralAST(){

}

std::string FloatLiteralAST::getAsString() const{
  return std::to_string(variable);
}

void FloatLiteralAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();

  t->setLabel(getAsString());
  dot->addSubtree(t);
}

void FloatLiteralAST::preOrder(std::function<void(AST*)> f){
  f(this);
}


void FloatLiteralAST::postOrder(std::function<void(AST*)> f, bool){
  f(this);
}

void FloatLiteralAST::evaluateType(std::ostream& os, SymbolTable &){
  dataType = VariableType::floatType;
  os<<"Set the data type of the float literal "<<getLineNumber()<<" to float"<<std::endl;
}

void FloatLiteralAST::generateICR(std::ostream&){
  //Create new temporary
  uniqueName = ICRepresentation::instance()->getUniqueVariableName();
  auto s = std::make_shared<Quadruple>(Quadruple::OperationType::copyF, std::to_string(variable), uniqueName);
  ICRepresentation::instance()->insert(s);
}

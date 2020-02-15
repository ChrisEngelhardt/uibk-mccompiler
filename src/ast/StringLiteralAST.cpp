#include<limits.h>

#include "../include/ast/StringLiteralAST.hpp"

using namespace MC;

StringLiteralAST::StringLiteralAST(std::string variable, int lineNumber):LiteralAST(stringType, lineNumber),variable(variable){
  std::string from = "\n";
  std::string to = "\\n";
  size_t start_pos = 0;
  while((start_pos = this->variable.find(from, start_pos)) != std::string::npos) {
    this->variable.replace(start_pos, from.length(), to);
    start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
  }

  setAstTypeString("StringLiteralAST: "+variable);
}

StringLiteralAST::~StringLiteralAST(){

}

std::string StringLiteralAST::getAsString() const{
  return variable;
}

void StringLiteralAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();

  t->setLabel(getAsString());
  dot->addSubtree(t);
}

void StringLiteralAST::preOrder(std::function<void(AST*)> f){
  f(this);
}

void StringLiteralAST::postOrder(std::function<void(AST*)> f, bool){
  f(this);
}

void StringLiteralAST::evaluateType(std::ostream& os, SymbolTable &){
  long length = variable.length()-2;
  if (length > LONG_MAX){
    throw(Semantic_Exception(std::to_string(lineNumber)+" String has length: " + std::to_string(length) + " but LONG_MAX is: " + std::to_string(LONG_MAX)));
  }

  dataType = VariableType::stringType;
  os<<"Set the data type of the string literal "<<getLineNumber()<<" to string"<<std::endl;
}

void StringLiteralAST::generateICR(std::ostream&){
  //Create new temporary
  uniqueName = ICRepresentation::instance()->getUniqueVariableName();
  auto s = std::make_shared<Quadruple>(Quadruple::OperationType::copyS, variable, uniqueName);
  ICRepresentation::instance()->insert(s);
}

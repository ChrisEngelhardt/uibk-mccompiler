#include "../include/ast/IdentifierAST.hpp"

#include "../include/SymbolTable/SymbolTable.hpp"

using namespace MC;

IdentifierAST::IdentifierAST(std::string name, int lineNumber):ExpressionAST(identifier, lineNumber),name(name),arrayType(VariableTypeArray(VariableType::undefined,-1)){
  setAstTypeString("Identifier: "+name);
}

IdentifierAST::~IdentifierAST(){

}

VariableTypeArray IdentifierAST::getArrayDataType(){
  return arrayType;
}

std::string IdentifierAST::getAsString() const{
  return name;
}

void IdentifierAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();


  t->setLabel(name);

  dot->addSubtree(t);
}

void IdentifierAST::preOrder(std::function<void(AST*)> f){
  f(this);
}

std::string IdentifierAST::getName(){
  return name;
}

void IdentifierAST::postOrder(std::function<void(AST*)> f, bool){
  f(this);
}

void IdentifierAST::evaluateType(std::ostream& os, SymbolTable &symbolTable){
  if(symbolTable.contains(name)){
    auto x = std::dynamic_pointer_cast<VarSymbol>(symbolTable.get(name));
    dataType = x->getIsArray() ? VariableType::undefined : x->getVarType().varType;
    arrayType = x->getVarType();
    uniqueName = x->uniqueName;
    os<<"The data types of the identifier "<<getName()<<" "<<getLineNumber()<<" was set to "<<AST::getVariableTypeAsString(dataType)<<std::endl;
  }
}

void IdentifierAST::generateICR(std::ostream&){

}

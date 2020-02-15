#include<limits.h>

#include "../include/ast/DeclarationStmtAST.hpp"

using namespace MC;

DeclarationStmtAST::DeclarationStmtAST(std::string variableType_, IdentifierAST_p identifier, int lineNumber):StmtAST(declarationStmt, lineNumber),variableType(AST::getVariableTypeFromString(variableType_)),identifier(identifier){
  setAstTypeString("DeclarationStmtAST: "+variableType_);
  this->arraySize = nullptr;
}

DeclarationStmtAST::DeclarationStmtAST(std::string variableType_, IdentifierAST_p identifier, IntLiteralAST_p arraySize, int lineNumber):StmtAST(declarationStmt, lineNumber),variableType(AST::getVariableTypeFromString(variableType_)),identifier(identifier),arraySize(arraySize){
  setAstTypeString("DeclarationStmtAST: "+variableType_);
}

DeclarationStmtAST::~DeclarationStmtAST(){

}

std::string DeclarationStmtAST::getAsString() const{
  return variableType+" "+identifier->getAsString();
}


std::string DeclarationStmtAST::getIdentifier() const{
  return identifier->getAsString();
}

IdentifierAST_p DeclarationStmtAST::getIdentifierAST(){
  return identifier;
}

VariableType DeclarationStmtAST::getType() const{
  return variableType;
}

VariableTypeArray DeclarationStmtAST::getTypeArray() const{
  if(arraySize == nullptr){
    return VariableTypeArray(variableType,-1);
  }
  return VariableTypeArray(variableType, arraySize->getVariable());
}

bool DeclarationStmtAST::isArray() const{
  return arraySize != nullptr;
}


void DeclarationStmtAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();


  if(arraySize == nullptr){
    t->setLabel("\""+getVariableTypeAsString(variableType)+" "+identifier->getAsString()+"\"");
  } else {
    t->setLabel("\""+getVariableTypeAsString(variableType)+" "+identifier->getAsString()+"["+arraySize->getAsString()+"]"+"\"");
  }

  dot->addSubtree(t);
}

void DeclarationStmtAST::preOrder(std::function<void(AST*)> f){
  f(this);
  identifier->preOrder(f);
  if(arraySize != nullptr){
    arraySize->preOrder(f);
  }
}


void DeclarationStmtAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  f(this);
  identifier->postOrder(f, deepTraversal);
  if(arraySize != nullptr){
    if(!deepTraversal){
      arraySize->postOrder(f, deepTraversal);
    }
  }
}

void DeclarationStmtAST::checkDeclaration(){
  if(arraySize != nullptr){
    if(arraySize->getVariable() <= 0){
      throw(Semantic_Exception(std::to_string(lineNumber)+" Array declaration "+identifier->getName()+" has a int value < 0"));
    }

    if(arraySize->getVariable() > LONG_MAX){
      throw(Semantic_Exception(std::to_string(lineNumber)+" Array declaration "+identifier->getName()+" has a int value > LONG_MAX"));
    }
  }
}

void DeclarationStmtAST::generateICR(std::ostream&){
  if(this->arraySize != nullptr){
    auto s = std::make_shared<Quadruple>(Quadruple::OperationType::declarationArray, arraySize->getAsString(), identifier->uniqueName);
    ICRepresentation::instance()->insert(s);
  }
}

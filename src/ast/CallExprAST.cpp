#include "../include/ast/CallExprAST.hpp"

using namespace MC;

CallExprAST::CallExprAST(IdentifierAST_p function, int lineNumber):ExpressionAST(callExpr, lineNumber),function(function){
  setAstTypeString("CallExpr");
  this->argumentList = nullptr;
}

CallExprAST::CallExprAST(IdentifierAST_p function, ArgumentsAST_p argumentList, int lineNumber):ExpressionAST(callExpr, lineNumber),function(function),argumentList(argumentList){
  setAstTypeString("CallExpr");
}

CallExprAST::~CallExprAST(){

}

void CallExprAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();


  t->setLabel("\""+function->getAsString()+"()"+"\"");

  if(argumentList != nullptr){
    argumentList->generateDOT(t);
  }

  dot->addSubtree(t);
}

void CallExprAST::preOrder(std::function<void(AST*)> f){
  f(this);
  function->preOrder(f);
  if(argumentList != nullptr){
    argumentList->preOrder(f);
  }
}

void CallExprAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  if(!deepTraversal){
    function->postOrder(f, deepTraversal);
  }
  if(argumentList != nullptr){
    argumentList->postOrder(f, deepTraversal);
  }
  f(this);
}

std::string CallExprAST::getFunctionIdentifier(){
  return function->getAsString();
}


std::vector<VariableTypeArray> CallExprAST::getArguments(){
  if(argumentList != nullptr){
    return argumentList->getArguments();
  }
  return std::vector<VariableTypeArray>();
}

void CallExprAST::evaluateType(std::ostream& os, SymbolTable &){
  SemanticChecks::instance()->checkIfFunctionCallIsValid(this);
  dataType = SemanticChecks::instance()->returnTypeOfCallExpr(this);

  os<<"The data type of the call expression "<<getLineNumber()<<" was set to "<<AST::getVariableTypeAsString(dataType)<<std::endl;
}


void CallExprAST::generateICR(std::ostream&){
  if (argumentList != NULL){
    auto list = argumentList->getArgumentVariableList();

    for(int i = list.size()-1; i>=0 ; i--){
      auto arg = list[i];
      auto argQ = std::make_shared<Quadruple>(Quadruple::OperationType::parameter,arg);
      ICRepresentation::instance()->insert(argQ);
    }
  }

  uniqueName = ICRepresentation::instance()->getUniqueVariableName();
  if(dataType == VariableType::floatType){
    auto funcQ = std::make_shared<Quadruple>(Quadruple::OperationType::pCallF, getFunctionIdentifier(),uniqueName);
    ICRepresentation::instance()->insert(funcQ);
  } else {
    auto funcQ = std::make_shared<Quadruple>(Quadruple::OperationType::pCall, getFunctionIdentifier(),uniqueName);
    ICRepresentation::instance()->insert(funcQ);
  }
}

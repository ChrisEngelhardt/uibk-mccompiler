#include "../include/ast/ReturnStmtAST.hpp"

using namespace MC;

ReturnStmtAST::ReturnStmtAST(int lineNumber):StmtAST(returnStmt, lineNumber){
  setAstTypeString("ReturnStmt");
  this->child = nullptr;
}

ReturnStmtAST::ReturnStmtAST(ExpressionAST_p child, int lineNumber):StmtAST(returnStmt, lineNumber),child(child){
  setAstTypeString("ReturnStmt");
}

ReturnStmtAST::~ReturnStmtAST(){

}

void ReturnStmtAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();

  t->setLabel("return");

  if(child != nullptr){
    child->generateDOT(t);
  }

  dot->addSubtree(t);
}

void ReturnStmtAST::preOrder(std::function<void(AST*)> f){
  f(this);
  if(child != nullptr){
    child->preOrder(f);
  }
}

void ReturnStmtAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  if(child != nullptr){
    child->postOrder(f, deepTraversal);
  }
  f(this);
}


VariableType ReturnStmtAST::getDataType(){
  if(child != nullptr){
    return child->getDataType();
  }
  return VariableType::voidType;
}

void ReturnStmtAST::generateICR(std::ostream&){
  if(child == nullptr){
    auto s = std::make_shared<Quadruple>(Quadruple::OperationType::rtrn,"");
    ICRepresentation::instance()->insert(s);
  } else {
    if(getDataType() == VariableType::floatType){
      auto s = std::make_shared<Quadruple>(Quadruple::OperationType::rtrnF,child->uniqueName);
      ICRepresentation::instance()->insert(s);
    } else {
      auto s = std::make_shared<Quadruple>(Quadruple::OperationType::rtrn,child->uniqueName);
      ICRepresentation::instance()->insert(s);
    }
  }
}

bool ReturnStmtAST::isLastStmtReturnStmt(){
  return true;
}

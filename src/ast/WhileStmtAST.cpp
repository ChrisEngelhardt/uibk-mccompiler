#include "../include/ast/WhileStmtAST.hpp"

using namespace MC;

WhileStmtAST::WhileStmtAST(ExpressionAST_p expression, StmtAST_p branch, int lineNumber):StmtAST(whileStmt, lineNumber),expression(expression),branch(branch){
  setAstTypeString("While");
}

WhileStmtAST::~WhileStmtAST(){

}

void WhileStmtAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();

  t->setLabel("while");

  expression->generateDOT(t);

  branch->generateDOT(t);

  dot->addSubtree(t);
}

void WhileStmtAST::preOrder(std::function<void(AST*)> f){
  f(this);
  expression->preOrder(f);
  branch->preOrder(f);
}

void WhileStmtAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  if(!deepTraversal){
    expression->postOrder(f, deepTraversal);
    branch->postOrder(f, deepTraversal);
  }
  f(this);
}

void WhileStmtAST::checkExpressionType(std::ostream& os){
  if(expression->getDataType() != VariableType::boolType){
    throw(Semantic_Exception(std::to_string(lineNumber)+" While statment didn't get a bool expression, but instead a " + AST::getVariableTypeAsString(expression->getDataType())));
  }
  os<<"Expression of the while statment "<<getLineNumber()<<" was a bool expression"<<std::endl;
}


void WhileStmtAST::generateICR(std::ostream& os){
  auto whileLabel = ICRepresentation::instance()->getUniqueLabelName();
  auto finallyLabel = ICRepresentation::instance()->getUniqueLabelName();


  auto whileQ = std::make_shared<Quadruple>(Quadruple::OperationType::label,whileLabel);
  ICRepresentation::instance()->insert(whileQ);

  expression->postOrder([&os](AST *ast){
    ast->generateICR(os);
  },true);

  auto conditionQ = std::make_shared<Quadruple>(Quadruple::OperationType::cJump, expression->uniqueName, finallyLabel);
  ICRepresentation::instance()->insert(conditionQ);

  branch->postOrder([&os](AST *ast){
    ast->generateICR(os);
  },true);

  auto jumpToTopQ = std::make_shared<Quadruple>(Quadruple::OperationType::ucJump, whileLabel);
  ICRepresentation::instance()->insert(jumpToTopQ);

  auto finallyQ = std::make_shared<Quadruple>(Quadruple::OperationType::label,finallyLabel);
  ICRepresentation::instance()->insert(finallyQ);
}

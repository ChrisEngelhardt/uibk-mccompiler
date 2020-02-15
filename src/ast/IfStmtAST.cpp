#include "../include/ast/IfStmtAST.hpp"
#include "../include/ast/CompoundStmtAST.hpp"
#include "../include/ast/ReturnStmtAST.hpp"



using namespace MC;

IfStmtAST::IfStmtAST(ExpressionAST_p expression, StmtAST_p ifBranch, int lineNumber):StmtAST(ifStmt, lineNumber),expression(expression),ifBranch(ifBranch){
  setAstTypeString("IfStmt");
  this->elseBranch = nullptr;
}


IfStmtAST::IfStmtAST(ExpressionAST_p expression, StmtAST_p ifBranch, StmtAST_p elseBranch, int lineNumber):StmtAST(ifStmt, lineNumber),expression(expression),ifBranch(ifBranch),elseBranch(elseBranch){
  setAstTypeString("IfStmt");
}

IfStmtAST::~IfStmtAST(){

}

void IfStmtAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();

  t->setLabel("if");

  expression->generateDOT(t);

  ifBranch->generateDOT(t);

  if(elseBranch != nullptr){
    elseBranch->generateDOT(t);
  }

  dot->addSubtree(t);
}

void IfStmtAST::preOrder(std::function<void(AST*)> f){
  f(this);
  expression->preOrder(f);
  ifBranch->preOrder(f);
  if(elseBranch != nullptr){
    elseBranch->preOrder(f);
  }
}

void IfStmtAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  expression->postOrder(f, deepTraversal);
  if(!deepTraversal){
    ifBranch->postOrder(f, deepTraversal);
    if(elseBranch != nullptr){
      elseBranch->postOrder(f, deepTraversal);
    }
  }
  f(this);
}

void IfStmtAST::checkExpressionType(std::ostream& os){
  if(expression->getDataType() != VariableType::boolType){
    throw(Semantic_Exception(std::to_string(lineNumber)+" If statment didn't get a bool expression, but instead a " + AST::getVariableTypeAsString(expression->getDataType())));
  }
  os<<"Expression of the if statment "<<getLineNumber()<<" was a bool expression"<<std::endl;
}

void IfStmtAST::generateICR(std::ostream& os){
  auto elseLabel = ICRepresentation::instance()->getUniqueLabelName();
  auto finallyLabel = ICRepresentation::instance()->getUniqueLabelName();

  auto conditionQ = std::make_shared<Quadruple>(Quadruple::OperationType::cJump, expression->uniqueName, elseLabel);
  ICRepresentation::instance()->insert(conditionQ);

  ifBranch->postOrder([&os](AST *ast){
    ast->generateICR(os);
  },true);

  auto jumpOut = std::make_shared<Quadruple>(Quadruple::OperationType::ucJump, finallyLabel);
  ICRepresentation::instance()->insert(jumpOut);


  auto elseQ = std::make_shared<Quadruple>(Quadruple::OperationType::label,elseLabel);
  ICRepresentation::instance()->insert(elseQ);

  if(elseBranch != nullptr){
    elseBranch->postOrder([&os](AST *ast){
      ast->generateICR(os);
    },true);
  }

  auto finallyQ = std::make_shared<Quadruple>(Quadruple::OperationType::label,finallyLabel);
  ICRepresentation::instance()->insert(finallyQ);
}


bool IfStmtAST::isLastStmtReturnStmt(){
  if(this->elseBranch == nullptr){
    return false;
  } else {
    return ifBranch->isLastStmtReturnStmt() && elseBranch->isLastStmtReturnStmt();
  }
}

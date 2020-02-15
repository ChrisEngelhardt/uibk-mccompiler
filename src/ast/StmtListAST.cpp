#include "../include/ast/StmtListAST.hpp"

#include <memory>

#include "../include/ast/ReturnStmtAST.hpp"
#include "../include/ast/IfStmtAST.hpp"

using namespace MC;

StmtListAST::StmtListAST():AST(statementL){
  setAstTypeString("StmtListAST");
}

StmtListAST::~StmtListAST(){

}


void StmtListAST::addStatement(StmtAST_p statement){
  statementList.push_back(statement);
}


void StmtListAST::generateDOT(DOTTree_p dot){
  for(auto statement : statementList){
    statement->generateDOT(dot);
  }
}

void StmtListAST::preOrder(std::function<void(AST*)> f){
  f(this);
  for (auto child : statementList){
    child->preOrder(f);
  }
}

void StmtListAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  for (auto child : statementList){
    child->postOrder(f, deepTraversal);
  }
  f(this);
}

bool StmtListAST::isLastStmtReturnStmt(){
  if(statementList.size()==0){
    return false;
  }
  return statementList.back()->isLastStmtReturnStmt();
}

void StmtListAST::generateICR(std::ostream&){

}

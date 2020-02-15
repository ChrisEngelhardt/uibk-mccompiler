#include "../include/ast/ExpressionStmtAST.hpp"

using namespace MC;

ExpressionStmtAST::ExpressionStmtAST(ExpressionAST_p expression, int lineNumber):StmtAST(expressionStmt, lineNumber),expression(expression){
}

ExpressionStmtAST::~ExpressionStmtAST(){

}

void ExpressionStmtAST::generateDOT(DOTTree_p dot){
  expression->generateDOT(dot);
}

void ExpressionStmtAST::preOrder(std::function<void(AST*)> f){
  f(this);
  expression->preOrder(f);
}

void ExpressionStmtAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  expression->postOrder(f, deepTraversal);
  f(this);
}

void ExpressionStmtAST::generateICR(std::ostream&){

}

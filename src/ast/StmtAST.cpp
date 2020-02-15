#include "../include/ast/StmtAST.hpp"

using namespace MC;

StmtAST::StmtAST(StmtAST::Type stmtType, int lineNumber):AST(statement, lineNumber),stmtType(stmtType){
  setAstTypeString("Statement");
}

StmtAST::~StmtAST(){

}

StmtAST::Type StmtAST::getStmtType(){
  return stmtType;
}


bool StmtAST::isLastStmtReturnStmt(){
  return false;
}

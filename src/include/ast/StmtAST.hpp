#ifndef __STMT_AST_HPP__
#define __STMT_AST_HPP__

#include "AST.hpp"

/**
 * The super class of the AST statement
 */
namespace MC{
  class StmtAST: public AST{
  public:
    enum Type{
      ifStmt, whileStmt, returnStmt, declarationStmt, assignmentStmt, expressionStmt, compoundStmt
    };

    /**
     * Create an StmtAST tree, given the statment astType
     * @param stmtType Type of the ast statment node
     * @param lineNumber line number in the code
     */
    StmtAST(StmtAST::Type stmtType, int lineNumber);
    ~StmtAST();

    /**
     * Returns the statment type
     * @return Statement type
     */
    StmtAST::Type getStmtType();

    /**
     * Checks if last statement is a return statment
     * @return is last statment a return statment
    */
    virtual bool isLastStmtReturnStmt();

  private:
    StmtAST::Type stmtType;
  };
}
#endif /* END __STMT_AST_HPP__ */

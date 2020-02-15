#ifndef __IF_STMT_AST_HPP__
#define __IF_STMT_AST_HPP__

#include "ExpressionAST.hpp"
#include "StmtAST.hpp"

/**
 * The AST class, which represents a if/else statement
 */
namespace MC{
  class IfStmtAST: public StmtAST{
  private:
    ExpressionAST_p expression;
    StmtAST_p ifBranch;
    StmtAST_p elseBranch;

  public:

    /**
     * Create a IfStmtAST tree, given a expression and a branch
     * @param expression If statment expression
     * @param ifBranch Branch of the if statment
     * @param lineNumber line number in the code
     */
    IfStmtAST(ExpressionAST_p expression, StmtAST_p ifBranch, int lineNumber);

    /**
     * Create a IfStmtAST tree, given a expression and a if-branch and a else-branch
     * @param expression If statment expression
     * @param ifBranch Branch of the if-statment
     * @param elseBranch Branch of the else-statment
     * @param lineNumber line number in the code
     */
    IfStmtAST(ExpressionAST_p expression, StmtAST_p ifBranch, StmtAST_p elseBranch, int lineNumber);
    ~IfStmtAST();

    /**
     * Creates a DOT note representation of the current node, which gets added to the parameter dot
     * @param dot dot tree where the current node should be added to
     */
    void generateDOT(DOTTree_p dot);

    /**
     * Traverses the tree in preOrder and executes function f on each compnent
     * @param f Funtion to call on each component.
     */
    void preOrder(std::function<void(AST*)> f);

    /**
     * Traverses the tree in postOrder and executes function f on each compnent
     * @param f Funtion to call on each component.
     */
    void postOrder(std::function<void(AST*)> f, bool deepTraversal);

    /**
     * Checks if the expression is a bool expression, if not, it thorws an error
     */
    void checkExpressionType(std::ostream& os);


    /**
     * Generates the ICR for the ast
     * @param os Output stream
     */
    void generateICR(std::ostream& os);

    /**
     * Checks if last statement is a return statment
     * @return is last statment a return statment
    */
    bool isLastStmtReturnStmt();
  };
}
#endif /* END __IF_STMT_AST_HPP__ */

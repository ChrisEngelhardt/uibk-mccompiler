#ifndef __WHILE_STMT_AST_HPP__
#define __WHILE_STMT_AST_HPP__

#include "ExpressionAST.hpp"
#include "StmtAST.hpp"

/**
 * The AST class, which represents a while statement
 */
namespace MC{
  class WhileStmtAST: public StmtAST{
  private:
    ExpressionAST_p expression;
    StmtAST_p branch;

  public:

    /**
     * Create a WhileStmtAST tree, given a expression and a branch
     * @param expression While statment expression
     * @param branch Branch of the while statment
     * @param lineNumber line number in the code
     */
    WhileStmtAST(ExpressionAST_p expression, StmtAST_p branch, int lineNumber);
    ~WhileStmtAST();

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
  };
}
#endif /* END __WHILE_STMT_AST_HPP__ */

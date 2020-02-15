#ifndef __EXPRESSION_STMT_AST_HPP__
#define __EXPRESSION_STMT_AST_HPP__

#include "ExpressionAST.hpp"
#include "StmtAST.hpp"

/**
 * The AST class, which represents a expression statement
 */
namespace MC{
  class ExpressionStmtAST: public StmtAST{
  private:
    ExpressionAST_p expression;

  public:

    /**
     * Create an ExpressionStmtAST tree, given the expression
     * @param expression Expression of the statement
     * @param lineNumber line number in the code
     */
    ExpressionStmtAST(ExpressionAST_p expression, int lineNumber);
    ~ExpressionStmtAST();

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
     * Generates the ICR for the ast
     * @param os Output stream
     */
      void generateICR(std::ostream&);
  };
}  

#endif /* END __EXPRESSION_STMT_AST_HPP__ */

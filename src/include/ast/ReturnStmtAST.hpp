#ifndef __RETURN_STMT_AST_HPP__
#define __RETURN_STMT_AST_HPP__

#include "ExpressionAST.hpp"
#include "StmtAST.hpp"

/**
 * The AST class, which represents a return statement
 */
namespace MC{
  class ReturnStmtAST: public StmtAST{
  private:
    ExpressionAST_p child;

  public:

    /**
     * Create an ReturnStmtAST tree
     * @param lineNumber line number in the code
     */
    ReturnStmtAST(int lineNumber);

    /**
     * Create an ReturnStmtAST tree, given an expression
     * @param child Expression, which should be returned
     * @param lineNumber line number in the code
     */
    ReturnStmtAST(ExpressionAST_p child, int lineNumber);
    ~ReturnStmtAST();

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
     * Returns the data type of the expression
     * @return the data type of the expression
     */
    VariableType getDataType();

    /**
     * Generates the ICR for the ast
     * @param os Output stream
     */
    void generateICR(std::ostream&);

    /**
     * Checks if last statement is a return statment
     * @return is last statment a return statment
    */
    bool isLastStmtReturnStmt();
  };
}
#endif /* END __RETURN_STMT_AST_HPP__ */

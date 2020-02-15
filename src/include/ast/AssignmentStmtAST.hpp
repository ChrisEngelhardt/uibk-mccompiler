#ifndef __ASSIGMENT_STMT_AST_HPP__
#define __ASSIGMENT_STMT_AST_HPP__

#include "ExpressionAST.hpp"
#include "IdentifierAST.hpp"
#include "StmtAST.hpp"

/**
 * The AST class, which represents an assignment statement
 */
namespace MC{
  class AssignmentStmtAST: public StmtAST{
  private:
    IdentifierAST_p identifier;
    ExpressionAST_p arrayExpression;
    ExpressionAST_p expression;
    std::string uniqueName = "";

  public:

    /**
     * Create an AssignmentStmtAST tree, given an identifier and an expression
     * @param identifier Identifier of the left side of the assignment
     * @param expression Expression of the value, which gets assignt to the identifier
     * @param lineNumber line number in the code
     */
    AssignmentStmtAST(IdentifierAST_p identifier, ExpressionAST_p expression, int lineNumber);

    /**
     * Create an AssignmentStmtAST tree, given a identifier and a arrayExpression, which represents an arrayIdentifier, and an expression
     * @param identifier Identifier of the array
     * @param arrayExpression Expression, which specifies the array entry
     * @param expression Expression of the value, which gets assignt to the identifier
     * @param lineNumber line number in the code
     */
    AssignmentStmtAST(IdentifierAST_p identifier, ExpressionAST_p arrayExpression, ExpressionAST_p expression, int lineNumber);
    ~AssignmentStmtAST();

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
     * Checks if the assignment assigns the right expression type to the identifier
     */
    void checkAssignment(std::ostream& os, SymbolTable &symbolTable);


    /**
     * Generates the ICR for the ast
     * @param os Output stream
     */
      void generateICR(std::ostream&);
  };
}
#endif /* END __ASSIGMENT_STMT_AST_HPP__ */

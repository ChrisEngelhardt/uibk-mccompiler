#ifndef __ARRAY_IDENTIFIER_AST_HPP__
#define __ARRAY_IDENTIFIER_AST_HPP__

#include "ExpressionAST.hpp"
#include "IdentifierAST.hpp"

/**
 * The AST class, which represents an array identifier
 */
namespace MC{
  class ArrayIdentifierAST: public ExpressionAST{
  private:
    IdentifierAST_p identifier;
    ExpressionAST_p arrayExpression;

  public:

    /**
     * Create an ArrayIdentifierAST tree, given an identifer and an arrayExpression
     * @param identifier Identifier of the array
     * @param arrayExpression Expression, which specifies the array entry
     * @param lineNumber line number in the code
     */
    ArrayIdentifierAST(IdentifierAST_p identifier, ExpressionAST_p arrayExpression, int lineNumber);
    ~ArrayIdentifierAST();

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
     * Evaluates the type of the expression
     * @param symbolTable symbolTable of the current scope
     */
    void evaluateType(std::ostream& os, SymbolTable &symbolTable);


    /**
     * Generates the ICR for the ast
     * @param os Output stream
     */
      void generateICR(std::ostream&);
  };
}

#endif /* END __ARRAY_IDENTIFIER_AST_HPP__ */

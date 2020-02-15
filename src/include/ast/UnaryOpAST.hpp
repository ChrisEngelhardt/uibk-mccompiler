#ifndef __UNARY_OP_AST_HPP__
#define __UNARY_OP_AST_HPP__

#include "ExpressionAST.hpp"

/**
 * The AST class, which represents a unary operation expression
 */
namespace MC{
  class UnaryOpAST: public ExpressionAST{
  private:
    std::string unaryOpType;
    ExpressionAST_p child;

  public:

    /**
     * Create a UnaryOpAST tree, given an operation type, and an expression
     * @param unaryOpType Type of the unary operation
     * @param child Expression of the binary operation
     * @param lineNumber line number in the code
     */
    UnaryOpAST(std::string unaryOpType, ExpressionAST_p child, int lineNumber);
    ~UnaryOpAST();

    /**
     * Returns the unary operation as a string
     * @return the unary operation as a string
     */
    std::string getUnaryOpType();

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
    virtual void evaluateType(std::ostream& os, SymbolTable &symbolTable);



    /**
     * Generates the ICR for the ast
     * @param os Output stream
     */
      void generateICR(std::ostream&);
  };
}

#endif /* END __UNARY_OP_AST_HPP__ */

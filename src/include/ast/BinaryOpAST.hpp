#ifndef __BINARY_OP_AST_HPP__
#define __BINARY_OP_AST_HPP__

#include "ExpressionAST.hpp"

/**
 * The AST class, which represents a binary operation expression
 */
namespace MC{
  class BinaryOpAST: public ExpressionAST{
  private:
    std::string binaryOpType;
    ExpressionAST_p lChild;
    ExpressionAST_p rChild;

  public:

    /**
     * Create a BinaryOpAST tree, given an operation type, and the left and right hand side of the expression
     * @param binaryOpType Type of the binary operation
     * @param lChild Left hand side of the binary operation
     * @param rChild Right hand side of the binary operation
     * @param lineNumber line number in the code
     */
    BinaryOpAST(std::string binaryOpType, ExpressionAST_p lChild,  ExpressionAST_p rChild, int lineNumber);
    ~BinaryOpAST();

    /**
     * Returns the binary operation as a string
     * @return the binary operation as a string
     */
    std::string getBinaryOpType();

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
#endif /* END __BINARY_OP_AST_HPP__ */

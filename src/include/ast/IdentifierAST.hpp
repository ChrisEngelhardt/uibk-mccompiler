#ifndef __IDENTIFIER_AST_HPP__
#define __IDENTIFIER_AST_HPP__

#include "ExpressionAST.hpp"

/**
 * The AST class, which represents an identifer
 */
namespace MC{
  class IdentifierAST: public ExpressionAST{
  private:
    std::string name;
    VariableTypeArray arrayType;

  public:

    /**
     * Create an IdentifierAST tree, given a name
     * @param name Name of the identifier
     */
    IdentifierAST(std::string name, int lineNumber);
    ~IdentifierAST();


    /**
     * Returns the array data type of the expression
     * @return the array data type of the expression
     */
    VariableTypeArray getArrayDataType();

    /**
     * Returns the AST node as a string. This coresponds to the DOT node representation
     * @return the AST subtype as a string
     */
    std::string getAsString() const;

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
     * Get the name of the identifier
     * @return name
     */
    std::string getName();

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
#endif /* END __IDENTIFIER_AST_HPP__ */

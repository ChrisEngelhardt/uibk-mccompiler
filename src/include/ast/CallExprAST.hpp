#ifndef __CALL_EXPR_AST_HPP__
#define __CALL_EXPR_AST_HPP__

#include "ArgumentsAST.hpp"
#include "ExpressionAST.hpp"
#include "IdentifierAST.hpp"
#include "include/SemanticChecks.hpp"

/**
 * The AST class, which represents a function call
 */
namespace MC{
  class CallExprAST: public ExpressionAST{
  private:
    IdentifierAST_p function;
    ArgumentsAST_p argumentList;

  public:

    /**
     * Create a CallExprAST tree, given a function identifier
     * @param identifier Identifier of the function, which gets called
     * @param lineNumber line number in the code
     */
    CallExprAST(IdentifierAST_p function, int lineNumber);

    /**
     * Create a CallExprAST tree, given a function identifier and a list of arguments
     * @param identifier Identifier of the function, which gets called
     * @param argumentList List of the arguments of the function call
     * @param lineNumber line number in the code
     */
    CallExprAST(IdentifierAST_p function, ArgumentsAST_p argumentList, int lineNumber);
    ~CallExprAST();

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
     * Getter for the function identifer
     * @return the funtion identifier.
     */
    std::string getFunctionIdentifier();


    /**
     * Getter for the argument list
     * @return argument list as std::vector<VariableTypeArray>
     */
    std::vector<VariableTypeArray> getArguments();

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

#endif /* END __CALL_EXPR_AST_HPP__ */

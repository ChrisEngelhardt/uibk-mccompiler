#ifndef __FUNCTION_AST_HPP__
#define __FUNCTION_AST_HPP__

#include "AST.hpp"
#include "CompoundStmtAST.hpp"
#include "IdentifierAST.hpp"
#include "ParametersAST.hpp"

/**
 * The AST class, which represents a function
 */
namespace MC{
  class FunctionAST: public AST{
  private:
    VariableType returnType;
    IdentifierAST_p identifier;
    CompoundStmtAST_p compoundStmt;
    ParametersAST_p  parameters;

  public:

    /**
     * Create a FunctionAST tree, given the return type, function name, and the body
     * @param returnType Return type of the function
     * @param identifier Name of the function
     * @param identifier Return type of the function
     * @param compoundStmt The body of the function, given as a compoundStmtAST
     * @param lineNumber line number in the code
     */
    FunctionAST(std::string returnType, IdentifierAST_p identifier, CompoundStmtAST_p compoundStmt, int lineNumber);

    /**
     * Create a FunctionAST tree, given the return type, function name, the body and the parameters
     * @param returnType Return type of the function
     * @param identifier Name of the function
     * @param identifier Return type of the function
     * @param compoundStmt The body of the function, given as a compoundStmtAST
     * @param parameters The parameters for the function
     * @param lineNumber line number in the code
     */
    FunctionAST(std::string returnType, IdentifierAST_p identifier, CompoundStmtAST_p compoundStmt, ParametersAST_p  parameters, int lineNumber);
    ~FunctionAST();

    /**
     * Returns the identifer of the function
     * @return Identifier of the function
     */
    IdentifierAST_p getIdentifier();

    /**
     * Returns the return value type of the function
     * @return return value type
     */
    VariableType getReturnType();

    /**
     * Returns all parameter types for this function
     * @return parameter types as vector
     */
    std::vector<VariableTypeArray> getParameters();

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
    * Generates the symbol table and does semantic checks for the function an all containing compound statements
    */
    void semanticAnalysis(std::ostream& os);


    /**
     * Prints the symbol table for the function and all contained comound statements
     */
    std::ostream& printSymbolTable(std::ostream& os);



    /**
     * Generates the ICR for the ast
     * @param os Output stream
     */
      void generateICR(std::ostream& os);

  };
}
#endif /* END __FUNCTION_AST_HPP__ */

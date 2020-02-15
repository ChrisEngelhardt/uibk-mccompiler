#ifndef __EXPRESSION_AST_HPP__
#define __EXPRESSION_AST_HPP__

#include "AST.hpp"

namespace MC{

  class SymbolTable;

  /**
   * The super class of the AST expression
   */
  class ExpressionAST: public AST{
  public:
    enum Type{
      literal, unaryOp, binaryOp, identifier, arrayIdentifier, callExpr
    };

    /**
     * Create an ExpressionAST tree, given the expression astType
     * @param expressionType type of the ast expression node
     * @param lineNumber line number in the code
     */
    ExpressionAST(ExpressionAST::Type expressionType, int lineNumber);
    ~ExpressionAST();

    /**
     * Returns the AST expression subtype
     * @return the AST expression subtype as ExpressionAST
     */
    ExpressionAST::Type getExpressionType();

    /**
     * Evaluates the type of the expression
     * @param symbolTable symbolTable of the current scope
     */
    virtual void evaluateType(std::ostream& os, SymbolTable &symbolTable);

    /**
     * Returns the data type of the expression
     * @return the data type of the expression
     */
    VariableType getDataType();

    std::string uniqueName = "";


  protected:
    VariableType dataType;

  private:
    ExpressionAST::Type expressionType;

  };
}

#endif /* END __EXPRESSION_AST_HPP__ */

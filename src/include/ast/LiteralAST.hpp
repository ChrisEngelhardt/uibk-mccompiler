#ifndef __LITERAL_AST_HPP__
#define __LITERAL_AST_HPP__

#include "ExpressionAST.hpp"

/**
 * The super class of the literal AST expression
 */
namespace MC{
  class LiteralAST: public ExpressionAST{
  public:
    enum Type{
      intType, floatType, stringType, boolType
    };

    /**
     * Create an LiteralAST tree, given the literal astType
     * @param literalType Type of the ast expression node
     * @param lineNumber line number in the code
     */
    LiteralAST(LiteralAST::Type literalType, int lineNumber);
    ~LiteralAST();

    /**
     * Returns the literal type
     * @return Literal type
     */
    Type getLiteralType();
  private:
    LiteralAST::Type literalType;
  };
}

#endif /* END __LITERAL_AST_HPP__ */

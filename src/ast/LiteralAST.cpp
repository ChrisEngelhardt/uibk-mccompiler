#include "../include/ast/LiteralAST.hpp"

using namespace MC;

LiteralAST::LiteralAST(LiteralAST::Type literalType, int lineNumber):ExpressionAST(literal, lineNumber),literalType(literalType){
  setAstTypeString("Literal");
}

LiteralAST::~LiteralAST(){

}

LiteralAST::Type LiteralAST::getLiteralType(){
  return literalType;
}

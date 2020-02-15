#include "../include/ast/ArrayIdentifierAST.hpp"

#include "../include/SymbolTable/SymbolTable.hpp"

using namespace MC;

ArrayIdentifierAST::ArrayIdentifierAST(IdentifierAST_p identifier, ExpressionAST_p arrayExpression, int lineNumber):ExpressionAST(arrayIdentifier, lineNumber),identifier(identifier),arrayExpression(arrayExpression){
  setAstTypeString("ArrayIdentifierAST");
}

ArrayIdentifierAST::~ArrayIdentifierAST(){

}

void ArrayIdentifierAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();

  t->setLabel("\""+identifier->getAsString()+"[]"+"\"");

  arrayExpression->generateDOT(t);

  dot->addSubtree(t);
}

void ArrayIdentifierAST::preOrder(std::function<void(AST*)> f){
  f(this);
  identifier->preOrder(f);
  arrayExpression->preOrder(f);
}

void ArrayIdentifierAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  identifier->postOrder(f, deepTraversal);
  arrayExpression->postOrder(f, deepTraversal);
  f(this);
}

void ArrayIdentifierAST::evaluateType(std::ostream& os, SymbolTable &symbolTable){
  if(arrayExpression->getDataType() != VariableType::intType){
    throw(Semantic_Exception(std::to_string(lineNumber)+" Array expression is not int, but " + AST::getVariableTypeAsString(arrayExpression->getDataType())));
  }
  if(symbolTable.contains(identifier->getName())){
    auto x = std::dynamic_pointer_cast<VarSymbol>(symbolTable.get(identifier->getName()));

    dataType = x->getIsArray() ? x->getVarType().varType :VariableType::undefined;
  } else {
    throw(Semantic_Exception(std::to_string(lineNumber)+" Could find the identifier " + identifier->getName()));
  }

  os<<"The data types of the array identifier "<<identifier->getName()<<" "<<getLineNumber()<<" was set to "<<AST::getVariableTypeAsString(dataType)<<std::endl;
}

void ArrayIdentifierAST::generateICR(std::ostream&){
  uniqueName = ICRepresentation::instance()->getUniqueVariableName();
  Quadruple::OperationType operationType;
  switch (dataType){
    case VariableType::intType:
    /* FALLTHRU */
    case VariableType::boolType:
      operationType = Quadruple::OperationType::copyFromArrayI;
      break;
    case VariableType::floatType:
      operationType = Quadruple::OperationType::copyFromArrayF;
      break;
    case VariableType::stringType:
      operationType = Quadruple::OperationType::copyFromArrayS;
      break;
    default:
      throw(ICR_Exception("Unsupported type for the array identifier"));
      break;
  }
  auto s = std::make_shared<Quadruple>(operationType, identifier->uniqueName, arrayExpression->uniqueName, uniqueName);
  ICRepresentation::instance()->insert(s);
}

#include "../include/ast/UnaryOpAST.hpp"

using namespace MC;

UnaryOpAST::UnaryOpAST(std::string unaryOpType, ExpressionAST_p child, int lineNumber):ExpressionAST(unaryOp, lineNumber),unaryOpType(unaryOpType),child(child){
  setAstTypeString("UnaryOP: "+unaryOpType);
}

UnaryOpAST::~UnaryOpAST(){

}

std::string UnaryOpAST::getUnaryOpType(){
  return unaryOpType;
}

void UnaryOpAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();


  t->setLabel("\""+unaryOpType+"\"");

  child->generateDOT(t);

  dot->addSubtree(t);
}

void UnaryOpAST::preOrder(std::function<void(AST*)> f){
  f(this);
  child->preOrder(f);
}

void UnaryOpAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  child->postOrder(f, deepTraversal);
  f(this);
}

void UnaryOpAST::evaluateType(std::ostream& os, SymbolTable &){
  if(child->getDataType() == VariableType::undefined) {
   throw(Semantic_Exception(std::to_string(lineNumber)+" Unsupported type for unary operation "+unaryOpType));
 } else if(unaryOpType == "-"){
    if(child->getDataType() != VariableType::intType && child->getDataType() != VariableType::floatType){
      throw(Semantic_Exception(std::to_string(lineNumber)+" Unmaching type " + AST::getVariableTypeAsString(child->getDataType()) + " for unary operation "+unaryOpType));
    } else {
      dataType = child->getDataType();
    }
  } else {
    if(child->getDataType() != VariableType::boolType){
      throw(Semantic_Exception(std::to_string(lineNumber)+" Unmaching type " + AST::getVariableTypeAsString(child->getDataType()) + " for unary operation "+unaryOpType));
    } else {
      dataType = child->getDataType();
    }
  }

  os<<"The data types for unary operation "<<getLineNumber()<<" "<<unaryOpType<<" were accepted"<<std::endl;

}

void UnaryOpAST::generateICR(std::ostream&){
  uniqueName = ICRepresentation::instance()->getUniqueVariableName();
  Quadruple::OperationType operationType;
  switch (child->getDataType()){
    case VariableType::intType:
    /* FALLTHRU */
    case VariableType::boolType:
      operationType = Quadruple::OperationType::unaryI;
      break;
    case VariableType::floatType:
      operationType = Quadruple::OperationType::unaryF;
      break;
    default:
      throw(ICR_Exception("Unsupported type for the unary operation"));
      break;
  }
  auto s = std::make_shared<OPQuadruple>(operationType, child->uniqueName, uniqueName, unaryOpType);
  ICRepresentation::instance()->insert(s);
}

#include "../include/ast/BinaryOpAST.hpp"

using namespace MC;

BinaryOpAST::BinaryOpAST(std::string binaryOpType, ExpressionAST_p lChild, ExpressionAST_p rChild, int lineNumber):ExpressionAST(unaryOp, lineNumber),binaryOpType(binaryOpType),lChild(lChild),rChild(rChild){
    setAstTypeString("BinaryOpAST: "+binaryOpType);
}

BinaryOpAST::~BinaryOpAST(){

}

std::string BinaryOpAST::getBinaryOpType(){
  return binaryOpType;
}

void BinaryOpAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();


  t->setLabel("\""+binaryOpType+"\"");

  lChild->generateDOT(t);
  rChild->generateDOT(t);

  dot->addSubtree(t);
}

void BinaryOpAST::preOrder(std::function<void(AST*)> f){
  f(this);
  lChild->preOrder(f);
  rChild->preOrder(f);
}

void BinaryOpAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  lChild->postOrder(f, deepTraversal);
  rChild->postOrder(f, deepTraversal);
  f(this);
}

void BinaryOpAST::evaluateType(std::ostream& os, SymbolTable &){
  if(lChild->getDataType() != rChild->getDataType()){
    throw(Semantic_Exception(std::to_string(lineNumber)+" Unmaching types " + AST::getVariableTypeAsString(lChild->getDataType()) + " " + AST::getVariableTypeAsString(rChild->getDataType()) + " for binary operation "+binaryOpType));
  } else if(binaryOpType == "+" || binaryOpType == "-" || binaryOpType == "*" || binaryOpType == "/" ) {
    if(lChild->getDataType() != VariableType::intType && lChild->getDataType() != VariableType::floatType){
      throw(Semantic_Exception(std::to_string(lineNumber)+" Unmaching type " + AST::getVariableTypeAsString(lChild->getDataType()) + " for binary operation "+binaryOpType));
    } else {
      dataType = lChild->getDataType();
    }
  } else if(lChild->getDataType() == VariableType::undefined) {
    throw(Semantic_Exception(std::to_string(lineNumber)+" Unsupported type for binary operation "+binaryOpType));
  } else {
    dataType = VariableType::boolType;
  }
  os<<"The data types for binary operation "<<getLineNumber()<<" "<<binaryOpType<<" matched"<<std::endl;
}

void BinaryOpAST::generateICR(std::ostream&){
  uniqueName = ICRepresentation::instance()->getUniqueVariableName();
  Quadruple::OperationType operationType;
  switch (lChild->getDataType()){
    case VariableType::intType:
    /* FALLTHRU */
    case VariableType::boolType:
      operationType = Quadruple::OperationType::binaryI;
      break;
    case VariableType::floatType:
      operationType = Quadruple::OperationType::binaryF;
      break;
    default:
      throw(ICR_Exception("Unsupported type for the binary operation"));
      break;
  }
  auto s = std::make_shared<OPQuadruple>(operationType, lChild->uniqueName, rChild->uniqueName , uniqueName, binaryOpType);
  ICRepresentation::instance()->insert(s);
}

#include "../include/astAll.hpp"
#include<limits.h>

using namespace MC;

AssignmentStmtAST::AssignmentStmtAST(IdentifierAST_p identifier, ExpressionAST_p expression, int lineNumber):StmtAST(assignmentStmt, lineNumber),identifier(identifier),expression(expression){
  setAstTypeString("AssignmentStmt");
  this->arrayExpression = nullptr;
}

AssignmentStmtAST::AssignmentStmtAST(IdentifierAST_p identifier, ExpressionAST_p arrayExpression, ExpressionAST_p expression, int lineNumber):StmtAST(assignmentStmt, lineNumber),identifier(identifier),arrayExpression(arrayExpression),expression(expression){
  setAstTypeString("AssignmentStmt");
}

AssignmentStmtAST::~AssignmentStmtAST(){

}

void AssignmentStmtAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();


  if(arrayExpression == nullptr){
    t->setLabel("\""+identifier->getAsString()+" ="+"\"");
    expression->generateDOT(t);
  } else {
    t->setLabel("\""+identifier->getAsString()+"[] ="+"\"");
    arrayExpression->generateDOT(t);
    expression->generateDOT(t);
  }

  dot->addSubtree(t);
}

void AssignmentStmtAST::preOrder(std::function<void(AST*)> f){
  f(this);
  identifier->preOrder(f);
  if(arrayExpression != nullptr){
    arrayExpression->preOrder(f);
  }
  expression->preOrder(f);
}

void AssignmentStmtAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  identifier->postOrder(f, deepTraversal);
  if(arrayExpression != nullptr){
    arrayExpression->postOrder(f, deepTraversal);
  }
  expression->postOrder(f, deepTraversal);
  f(this);
}

void AssignmentStmtAST::checkAssignment(std::ostream& os, SymbolTable &symbolTable){
  if(arrayExpression == nullptr){
    if(identifier->getDataType()==VariableType::undefined){
      throw(Semantic_Exception(std::to_string(lineNumber)+" Identifier "+identifier->getName()+" has a undefined data type"));
    }
    if(identifier->getDataType()!=expression->getDataType()){
      throw(Semantic_Exception(std::to_string(lineNumber)+" Assignment type mismatch "+AST::getVariableTypeAsString(identifier->getDataType())+" "+AST::getVariableTypeAsString(expression->getDataType())+" for "+identifier->getName()));
    }
  } else {
    if(arrayExpression->getDataType() != VariableType::intType){
      throw(Semantic_Exception(std::to_string(lineNumber)+" Array expression is not int, but " + AST::getVariableTypeAsString(arrayExpression->getDataType())));
    }
    if(symbolTable.contains(identifier->getName())){
      auto x = std::dynamic_pointer_cast<VarSymbol>(symbolTable.get(identifier->getName()));

      VariableType identiferType = x->getIsArray() ? x->getVarType().varType :VariableType::undefined;

      if(identiferType==VariableType::undefined){
        throw(Semantic_Exception(std::to_string(lineNumber)+" Identifier "+identifier->getName()+" has a undefined data type"));
      }

      if(identiferType!=expression->getDataType()){
        throw(Semantic_Exception(std::to_string(lineNumber)+" Assignment type mismatch "+AST::getVariableTypeAsString(identiferType)+" "+AST::getVariableTypeAsString(expression->getDataType())+" for "+identifier->getName()));
      }
    } else {
      throw(Semantic_Exception(std::to_string(lineNumber)+" Could find the identifier " + identifier->getName()));
    }
  }

  os<<"The data types of the assignment statment "<<getLineNumber()<<" are matching"<<std::endl;
}

void AssignmentStmtAST::generateICR(std::ostream&){
  if(arrayExpression == nullptr){
    Quadruple::OperationType operationType = Quadruple::OperationType::copyI;
    switch (identifier->getDataType()){
      case VariableType::intType:
      /* FALLTHRU */
      case VariableType::boolType:
        operationType = Quadruple::OperationType::copyI;
        break;
      case VariableType::floatType:
        operationType = Quadruple::OperationType::copyF;
        break;
      case VariableType::stringType:
        operationType = Quadruple::OperationType::copyS;
        break;
      default:
        throw(ICR_Exception("Unsupported type for the assigment statement"));
        break;
    }
    auto s = std::make_shared<Quadruple>(operationType, expression->uniqueName, identifier->uniqueName);
    ICRepresentation::instance()->insert(s);
  } else {

    Quadruple::OperationType operationType = Quadruple::OperationType::copyToArrayI;;
    switch (expression->getDataType()){
      case VariableType::intType:
      /* FALLTHRU */
      case VariableType::boolType:
        operationType = Quadruple::OperationType::copyToArrayI;
        break;
      case VariableType::floatType:
        operationType = Quadruple::OperationType::copyToArrayF;
        break;
      case VariableType::stringType:
        operationType = Quadruple::OperationType::copyToArrayS;
        break;
      default:
        break;
    }
    auto s = std::make_shared<Quadruple>(operationType, expression->uniqueName, arrayExpression->uniqueName, identifier->uniqueName);
    ICRepresentation::instance()->insert(s);
  }

}

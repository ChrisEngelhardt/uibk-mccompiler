#include "../include/ast/FunctionAST.hpp"

using namespace MC;

FunctionAST::FunctionAST(std::string returnType_, IdentifierAST_p identifier, CompoundStmtAST_p compoundStmt, int lineNumber):AST(function, lineNumber),returnType(AST::getVariableTypeFromString(returnType_)),identifier(identifier),compoundStmt(compoundStmt){
  setAstTypeString("Function returns: "+returnType_);
  parameters = nullptr;
}

FunctionAST::FunctionAST(std::string returnType_, IdentifierAST_p identifier, CompoundStmtAST_p compoundStmt, ParametersAST_p  parameters, int lineNumber):AST(function, lineNumber),returnType(AST::getVariableTypeFromString(returnType_)),identifier(identifier),compoundStmt(compoundStmt),parameters(parameters){
  setAstTypeString("Function returns: "+returnType_);
}

FunctionAST::~FunctionAST(){

}

IdentifierAST_p FunctionAST::getIdentifier(){
  return identifier;
}

VariableType FunctionAST::getReturnType(){
  return returnType;
}

std::vector<VariableTypeArray> FunctionAST::getParameters(){
  std::vector<VariableTypeArray> para;
  if (parameters == NULL) return para;
  for (auto p : *parameters->getParameterList()){
    if (p != NULL){
      para.push_back(p->getTypeArray());
    }
  }
  return para;
}

void FunctionAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();


  if (parameters == nullptr){
    t->setLabel("\""+getVariableTypeAsString(returnType)+" "+identifier->getAsString()+"()"+"\"");
  } else {
    t->setLabel("\""+getVariableTypeAsString(returnType)+" "+identifier->getAsString()+"("+parameters->getAsString()+")"+"\"");
  }
  t->setEdgeLabel("Function");
  compoundStmt->generateDOT(t);

  dot->addSubtree(t);
}

void FunctionAST::preOrder(std::function<void(AST*)> f){
  f(this);
  identifier->preOrder(f);
  compoundStmt->preOrder(f);
  if(parameters != nullptr){
    parameters->preOrder(f);
  }
}

void FunctionAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  identifier->postOrder(f, deepTraversal);
  compoundStmt->postOrder(f, deepTraversal);
  if(parameters != nullptr){
    parameters->postOrder(f, deepTraversal);
  }
  f(this);
}

void FunctionAST::semanticAnalysis(std::ostream& os){
  os<<"Starting semantic analysis of "<<identifier->getAsString()<<"()"<<std::endl;
  if(parameters != nullptr){
    os<<"Adding parameters to symbol tabel"<<std::endl;
    compoundStmt->mergesParameterListIntoSymbolTable(os, parameters->getParameterList());
  }
  VariableType inferredReturnType = compoundStmt->semanticAnalysis(os);
  SemanticChecks::instance()->checkForReturnType(os, this, inferredReturnType);
}


std::ostream& FunctionAST::printSymbolTable(std::ostream& os){
    preOrder([this, &os](AST *ast){
      CompoundStmtAST* c = dynamic_cast<CompoundStmtAST*>(ast);
      if( c != NULL ){
        std::string ident= identifier->getAsString() + "()  ";
        c->printSymbolTable(ident, os);
      }
    });
    return os;
}

void FunctionAST::generateICR(std::ostream& os){
  //Create label for function
  auto s = std::make_shared<Quadruple>(Quadruple::OperationType::labelF,identifier->getAsString(), "");
  ICRepresentation::instance()->insert(s);

  if(parameters != nullptr){
    parameters->generateICR(os);
  }

  compoundStmt->postOrder([&os](AST *ast){
    ast->generateICR(os);
  },true);

  if (returnType == VariableType::voidType){
    auto s = std::make_shared<Quadruple>(Quadruple::OperationType::rtrn,"","");
    ICRepresentation::instance()->insert(s);
  }
}

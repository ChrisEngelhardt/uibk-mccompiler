#include "include/SemanticChecks.hpp"

#include "include/astAll.hpp"

using namespace MC;

void SemanticChecks::checkForUniqueSymbol(SymbolTable *st, SymIdent identifier){
  if (st->contains(identifier)){
      throw(Semantic_Exception("Variable defined twice"));
  }
}


void SemanticChecks::checkMainFunction(){
  //Check if programm contains main function
  if (!fnt->contains("main")){
    throw(Semantic_Exception("No main function defined"));
  }

  //Check if main function has correct signature
  auto x = std::dynamic_pointer_cast<BuiltInFunctionSymbol> (fnt->get("main"));
  if (x->parameter.size() != 0){
    throw(Semantic_Exception("main function has wrong signature"));
  }

  if (x->returnType != VariableType::intType){
    throw(Semantic_Exception("main function has wrong signature"));
  }
}


void SemanticChecks::checkForUniqueFunction(std::ostream& os, SymIdent identifier){
  if (fnt->contains(identifier)){
      throw(Semantic_Exception("Function " + identifier+ "() defined twice"));
  }
  os<<"Function "<<identifier<<" was not previously defined"<<std::endl;
}


void SemanticChecks::checkIfFunctionCallIsValid(CallExprAST *ast){
  //Check if function exist
  std::string fn = ast->getFunctionIdentifier();
  if (!fnt->contains(fn)){
    throw(Semantic_Exception("Function " + fn+ "() not defined"));
  }


  //Check for matching parameters
  std::vector<VariableTypeArray> parameters1 = std::dynamic_pointer_cast<BuiltInFunctionSymbol>(fnt->get(fn))->parameter;
  std::vector<VariableTypeArray> parameters2 = ast->getArguments();
  if (parameters1 != parameters2){
    throw(Semantic_Exception("Function call " + fn+ "() did not match its definition"));
  }

}


VariableType SemanticChecks::returnTypeOfCallExpr(CallExprAST *ast){
  //Check if function exist
  std::string fn = ast->getFunctionIdentifier();
  if (!fnt->contains(fn)){
    throw(Semantic_Exception("Function " + fn+ "() not defined"));
  }
  return std::dynamic_pointer_cast<BuiltInFunctionSymbol>(fnt->get(fn))->returnType;
}


void SemanticChecks::checkForReturnType(std::ostream& os, FunctionAST *ast, VariableType typeB){
  if (ast->getReturnType() != typeB){
    throw(Semantic_Exception("Return type of function " + ast->getIdentifier()->getName() + "() did not match definition"));
  }

  os<<"Return type of "<<ast->getIdentifier()->getName()<<"() "<<ast->getLineNumber()<<" matched the definition"<<std::endl;
}


void SemanticChecks::checkIfVariableIsDefined(std::ostream& os, SymbolTable *symbolTable, IdentifierAST *ast){
  if(fnt->contains(ast->getName())) return;
  if (!symbolTable->contains(ast->getName())){
    throw(Semantic_Exception("Used symbol \"" + ast->getName() + "\" is not defined in scope"));
  }
  os<<"Symbol "<<ast->getName()<<" "<<ast->getLineNumber()<<" is part of the symbol tabel"<<std::endl;
}

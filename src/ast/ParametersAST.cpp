#include "../include/ast/ParametersAST.hpp"

using namespace MC;

ParametersAST::ParametersAST():AST(parameters){
  setAstTypeString("ParameterAST");

}

ParametersAST::~ParametersAST(){

}

void ParametersAST::addParameter(DeclarationStmtAST_p parameter){
  parameterList.push_back(parameter);
}

std::string ParametersAST::getAsString() const{
  std::string parameters= "";
  std::for_each(parameterList.begin(), parameterList.end(), [&parameters](DeclarationStmtAST_p dec){ parameters += dec->getAsString() + ", "; });
  return parameters.substr(0, parameters.size()-2);
}

void ParametersAST::preOrder(std::function<void(AST*)> f){
  f(this);
  for (auto child : parameterList){
    child->preOrder(f);
  }
}

void ParametersAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  for (auto child : parameterList){
    child->postOrder(f, deepTraversal);
  }
  f(this);
}

std::vector<DeclarationStmtAST_p>* ParametersAST::getParameterList(){
  return &parameterList;
}

void ParametersAST::generateICR(std::ostream&){
  for (auto child : parameterList){
    auto s = std::make_shared<Quadruple>(Quadruple::OperationType::parameterF, "",child->getIdentifierAST()->uniqueName);
    ICRepresentation::instance()->insert(s);
  }
}

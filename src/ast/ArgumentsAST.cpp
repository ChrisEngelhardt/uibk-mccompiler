#include "../include/ast/ArgumentsAST.hpp"

#include "../include/ast/IdentifierAST.hpp"

using namespace MC;

ArgumentsAST::ArgumentsAST():AST(arguments){
  setAstTypeString("ArgumentsAST");

}

ArgumentsAST::~ArgumentsAST(){

}

void ArgumentsAST::addArgument(ExpressionAST_p expression){
  argumentList.push_back(expression);
}


void ArgumentsAST::generateDOT(DOTTree_p dot){
  for(auto argument : argumentList){
    argument->generateDOT(dot);
  }
}

void ArgumentsAST::preOrder(std::function<void(AST*)> f){
  f(this);
  for (auto child : argumentList){
    child->preOrder(f);
  }
}

void ArgumentsAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  for (auto child : argumentList){
    child->postOrder(f, deepTraversal);
  }
  f(this);
}


std::vector<VariableTypeArray> ArgumentsAST::getArguments(){
  std::vector<VariableTypeArray> args;
  for (auto e : argumentList){
    IdentifierAST* i = dynamic_cast<IdentifierAST*>(e.get());
    if( i != NULL ){
      args.push_back(i->getArrayDataType());
    } else {
      args.push_back(VariableTypeArray(e->getDataType(),-1));
    }
  }

  return args;
}

  std::vector<std::string> ArgumentsAST::getArgumentVariableList(){
    std::vector<std::string> variableList;

    for (auto arg : argumentList){
     if( arg != NULL ){
       variableList.push_back(arg->uniqueName);
     }
    }

    return variableList;
  }


void ArgumentsAST::generateICR(std::ostream&){

}

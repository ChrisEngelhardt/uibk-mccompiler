#include "../include/ast/ProgramAST.hpp"

#include <sstream>
#include <string>

using namespace MC;

ProgramAST::ProgramAST():AST(program){
  setAstTypeString("Programm");
}

ProgramAST::~ProgramAST(){
  SemanticChecks::destroyInstance();
  ICRepresentation::destroyInstance();
}

void ProgramAST::addFunction(std::shared_ptr<FunctionAST> function){
  functionList.push_back(function);
}

void ProgramAST::preOrder(std::function<void(AST*)> f){
  f(this);
  for (auto child : functionList){
    child->preOrder(f);
  }
}

void ProgramAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  for (auto child : functionList){
    child->postOrder(f, deepTraversal);
  }
  f(this);
}

std::vector<FunctionAST_p>* ProgramAST::getFunctionList(){
  return &functionList;
}


void ProgramAST::generateBuiltIns(){
  std::vector<VariableTypeArray> parameter = {VariableTypeArray(VariableType::stringType,-1)};
  functionTable.insert(std::make_shared<BuiltInFunctionSymbol>("print", parameter, VariableType::voidType));
  parameter = {};
  functionTable.insert(std::make_shared<BuiltInFunctionSymbol>("print_nl", parameter, VariableType::voidType));
  parameter = {VariableTypeArray(VariableType::intType,-1)};
  functionTable.insert(std::make_shared<BuiltInFunctionSymbol>("print_int", parameter, VariableType::voidType));
  parameter = {VariableTypeArray(VariableType::floatType,-1)};
  functionTable.insert(std::make_shared<BuiltInFunctionSymbol>("print_float", parameter, VariableType::voidType));
  parameter = {};
  functionTable.insert(std::make_shared<BuiltInFunctionSymbol>("read_int", parameter, VariableType::intType));
  parameter = {};
  functionTable.insert(std::make_shared<BuiltInFunctionSymbol>("read_float", parameter, VariableType::floatType));
}

void ProgramAST::generateFunctionTable(std::ostream& os){
  generateBuiltIns();
  for (auto f : functionList){
      std::vector<VariableTypeArray> parameter = f->getParameters();
      SemanticChecks::instance()->checkForUniqueFunction(os, f->getIdentifier()->getAsString());
      functionTable.insert(std::make_shared<FunctionSymbol>(f->getIdentifier()->getAsString(), parameter, f->getReturnType()));
  }
}


void ProgramAST::semanticAnalysis(std::ostream& os, const std::string function){
  SemanticChecks::instance(&functionTable);

  if(function == ""){
    generateFunctionTable(os);
    SemanticChecks::instance()->checkMainFunction();
    os<<"Found main funtion with correct signature"<<std::endl;
    for (auto f : functionList){
      f->semanticAnalysis(os);
    }

  } else {
    std::ostringstream osTmp;
    generateFunctionTable(osTmp);
    SemanticChecks::instance()->checkMainFunction();
    for (auto f : functionList){
      if (f->getIdentifier()->getAsString() == function){
        f->semanticAnalysis(os);
      } else {
        f->semanticAnalysis(osTmp);
      }
    }
  }

}



void ProgramAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();

  t->setLabel("Programm");
  for(auto function : functionList){
    function->generateDOT(t);
  }

  dot->addSubtree(t);
}

std::shared_ptr<DOTTree> ProgramAST::getAsDot(){
  auto tree = std::make_shared<DOTTree>();

  tree->setLabel("Programm");
  for(auto function : functionList){
    function->generateDOT(tree);
  }

  tree->setCustomBoxAttributesForEach("shape=box");

  return tree;
}


std::shared_ptr<DOTTree> ProgramAST::getAsDot(const std::string function){
  auto tree = std::make_shared<DOTTree>();

  for(auto fn : functionList){
    std::string functionName = fn->getIdentifier()->getAsString();
    if (functionName.compare(function) == 0){
      fn->generateDOT(tree);
      return tree;
    }
  }
  throw(AST_Exception("Function not found"));
}

std::ostream& ProgramAST::getSymbolTable(std::ostream& os){
  if(functionTable.size() == 0) { throw(MC::MCC_Exception("No symbol table. Please do semanticCheck() before.")); }

  functionTable.printContent("\nGlobal function Table", os);

  for(auto fn : functionList)
      fn->printSymbolTable(os);

  return os;
}

std::ostream& ProgramAST::getSymbolTable(std::ostream& os, const std::string function){
  if(functionTable.size() == 0) { throw(MC::MCC_Exception("No symbol table. Please do semanticCheck() before.")); }
  if(!functionTable.contains(function)) { throw(MC::MCC_Exception("Function not found")); }
  for(auto fn : functionList){
    std::string functionName = fn->getIdentifier()->getAsString();
    if (functionName.compare(function) == 0){
      return fn->printSymbolTable(os);
    }
  }
  throw(AST_Exception("Function not found"));
}


  void ProgramAST::generateICR(std::ostream& os){
    for (auto f : functionList){
      f->generateICR(os);
    }
  }

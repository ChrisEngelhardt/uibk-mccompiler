#include "../include/ast/CompoundStmtAST.hpp"

#include "../include/ast/AssignmentStmtAST.hpp"
#include "../include/ast/DeclarationStmtAST.hpp"
#include "../include/ast/FunctionAST.hpp"
#include "../include/ast/IfStmtAST.hpp"
#include "../include/ast/ReturnStmtAST.hpp"
#include "../include/ast/WhileStmtAST.hpp"

using namespace MC;

CompoundStmtAST::CompoundStmtAST(StmtListAST_p branch, int lineNumber):StmtAST(compoundStmt, lineNumber),branch(branch){
    setAstTypeString("CompoundStmtAST");
}

CompoundStmtAST::~CompoundStmtAST(){

}


void CompoundStmtAST::generateDOT(DOTTree_p dot){
  DOTTree_p t = std::make_shared<DOTTree>();
  t->setLabel("\"{ }\"");
  t->setEdgeLabel("body");
  branch->generateDOT(t);
  dot->addSubtree(t);
}

void CompoundStmtAST::preOrder(std::function<void(AST*)> f){
  f(this);
}

void CompoundStmtAST::postOrder(std::function<void(AST*)> f, bool deepTraversal){
  if(deepTraversal){
    branch->postOrder(f, deepTraversal);
  }
  f(this);
}

VariableType CompoundStmtAST::semanticAnalysis(std::ostream& os){
  os<<"Starting analysis of compound statement "<<getLineNumber()<<std::endl;
  VariableType returnType = VariableType::undefined;


  branch->postOrder([this,&os,&returnType](AST *ast){
    //Check for variable definiton
    isOfType<DeclarationStmtAST>(ast,[this,&os](DeclarationStmtAST* d){
      d->checkDeclaration();
      try{
        symbolTable.insert(std::make_shared<VarSymbol>(d->getIdentifier(),d->getTypeArray()));
        os<<"Added "<<d->getIdentifier()<<" "<<d->getLineNumber()<<" to the symbol tabel"<<std::endl;
      }catch(const char *err ){
        std::cout << err << std::endl;
      }
    });

    //Check for compound statements
    isOfType<CompoundStmtAST>(ast,[this,&os,&returnType](CompoundStmtAST* c){
      os<<"Mergeing symbols of compound statement "<<getLineNumber()<<" into compound statement "<<getLineNumber()<<std::endl;
      c->mergeSymbolTable(symbolTable);

      VariableType compoundReturn = c->semanticAnalysis(os);
      if(returnType == VariableType::undefined && compoundReturn != VariableType::voidType){
        returnType = compoundReturn;
      }
    });


    //Check if used variables are already defined in scope
    isOfType<ExpressionAST>(ast,[this,&os](ExpressionAST *e){
      if (e->getExpressionType() != ExpressionAST::Type::callExpr){
        isOfType<IdentifierAST>(e,[this,&os](IdentifierAST *i){
          SemanticChecks::instance()->checkIfVariableIsDefined(os,&symbolTable, i);
        });
      }
    });


    isOfType<ExpressionAST>(ast,[this,&os](ExpressionAST* e){
      e->evaluateType(os, symbolTable);
    });

    isOfType<ReturnStmtAST>(ast,[this,&os,&returnType](ReturnStmtAST* r){
      if(returnType == VariableType::undefined){
        returnType = r->getDataType();
      } else if(returnType != r->getDataType()) {
        throw(Semantic_Exception(std::to_string(lineNumber)+" Return types of do not match"));
      }
    });

    isOfType<AssignmentStmtAST>(ast,[this,&os](AssignmentStmtAST* a){
      a->checkAssignment(os, symbolTable);
    });

    isOfType<IfStmtAST>(ast,[this,&os](IfStmtAST* i){
      i->checkExpressionType(os);
    });

    isOfType<WhileStmtAST>(ast,[this,&os](WhileStmtAST* w){
      w->checkExpressionType(os);
    });
  },false);

  if(branch->isLastStmtReturnStmt()){
    return returnType;
  }

  return  VariableType::voidType;
}

bool CompoundStmtAST::isLastStmtReturnStmt(){
  return branch->isLastStmtReturnStmt();
}

std::ostream& CompoundStmtAST::printSymbolTable(std::string functionScope, std::ostream& os){
  symbolTable.printContent(functionScope + "Row:" + std::to_string(lineNumber), os);
  branch->preOrder([&os, &functionScope](AST *ast){
      CompoundStmtAST* j = dynamic_cast<CompoundStmtAST*>(ast);
      if( j != NULL ){
        j->printSymbolTable(functionScope , os);
      }
  });

  return os;
}

void CompoundStmtAST::mergeSymbolTable(SymbolTable inTable){
  symbolTable.merge(inTable);
}

void CompoundStmtAST::mergesParameterListIntoSymbolTable(std::ostream& os, std::vector<DeclarationStmtAST_p>* parameterList){
  if(parameterList != nullptr){
    for(auto parameter: *parameterList){
      os<<"Adding parameter "<<parameter->getIdentifier()<<" to the symbol tabel"<<std::endl;
      symbolTable.insert(std::make_shared<VarSymbol>(parameter->getIdentifier(),parameter->getTypeArray()));
      parameter->getIdentifierAST()->evaluateType(os, symbolTable);
    }
  }
}

void CompoundStmtAST::generateICR(std::ostream&){

}

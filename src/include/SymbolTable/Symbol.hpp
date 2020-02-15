#ifndef UNTITLED_SYMBOL_H
#define UNTITLED_SYMBOL_H

#include <iostream>

#include "include/ast/LiteralAST.hpp"

namespace MC{

  typedef std::string SymIdent ;

  struct Symbol{
  public:
      SymIdent identifier;
      std::vector<AST_p> references;
      std::string type = "Symbol";
      bool merged = false;


      Symbol(const SymIdent &identifier) : identifier(identifier) {}
      virtual ~Symbol(){}

      SymIdent getIdentifier(){
        return identifier;
      }

      void addReference(AST_p ast){
        references.push_back(ast);
      }

      std::vector<AST_p> getReferences(){
        return references;
      }

      int getReferencesCount(){
        return references.size();
      }


  };

  struct VarSymbol: public Symbol{
    VariableTypeArray varType;
    std::string uniqueName = "";


    VarSymbol(const SymIdent &identifier, VariableTypeArray varType): Symbol(identifier) , varType(varType){
      uniqueName = MC::ICRepresentation::instance()->getUniqueVariableName();
    }

    std::string getVarTypeAsString(){
      return AST::getVariableTypeAsString(varType);
    }

    VariableTypeArray getVarType(){
      return varType;
    }

    bool getIsArray(){
      return varType.arraySize != -1;
    }
  };


  struct BuiltInFunctionSymbol: public Symbol{
  public:
      std::vector<VariableTypeArray> parameter;
      VariableType returnType;

      BuiltInFunctionSymbol(const SymIdent &identifier, std::vector<VariableTypeArray> parameter, VariableType returnType) : Symbol(identifier), parameter(parameter), returnType(returnType){
        type = "Built-In";
      }

      std::string getParameters(){
        std::string retval =  "[";
        bool first = true;
        for (auto p : parameter)
          if (first == true){
            retval += AST::getVariableTypeAsString(p);
            first = false;
          }else{
            retval +=  ", " + AST::getVariableTypeAsString(p);
          }
          return retval + "]";
      }


      std::string getReturnType(){
        return AST::getVariableTypeAsString(returnType);
      }

  };

  struct FunctionSymbol: public BuiltInFunctionSymbol{
    FunctionSymbol(const SymIdent &identifier, std::vector<VariableTypeArray> parameter, VariableType returnValue) : BuiltInFunctionSymbol(identifier, parameter, returnValue){
      type = "User-Defined";
    }
  };

  typedef std::shared_ptr<Symbol> Symbol_p;
  typedef std::shared_ptr<VarSymbol> VarSymbol_p;
  typedef std::shared_ptr<BuiltInFunctionSymbol> BuiltInFunctionSymbol_p;
  typedef std::shared_ptr<FunctionSymbol> FunctionSymbol_p;
}

#endif //UNTITLED_SYMBOL_H

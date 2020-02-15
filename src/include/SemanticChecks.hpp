#ifndef UNTITLED_SEMANTICCHECKS_H
#define UNTITLED_SEMANTICCHECKS_H

#include <iostream>

#include "include/SymbolTable/FunctionTable.hpp"
#include "include/SymbolTable/SymbolTable.hpp"
#include "include/utils/Singleton.hpp"

namespace MC{
class SemanticChecks: public Singleton <SemanticChecks>{
private:
  friend class Singleton <SemanticChecks>;
  FunctionTable* fnt;

 protected:
    SemanticChecks(FunctionTable* fnt): fnt(fnt) { }
    SemanticChecks(){ }

public:


  /**
   * Check if given symbol is unique and not already in list
   * @param st list which could contain symbol
   * @param s symbol to check
   */
   void checkForUniqueSymbol(SymbolTable *st, SymIdent identifier);

   /**
    * Check for main function and correct defition
    * @param functionTable function table from root ast
    */
   void checkMainFunction();

   /**
    * Check that each function is only defined once
    * @param functionTable function table from root ast
    */
   void checkForUniqueFunction(std::ostream& os, SymIdent identifier);


   /**
    * Checks that called function exists and that it matches it definition
    * @param ast CallExpr ast
    */
   void checkIfFunctionCallIsValid(CallExprAST *ast);

   /**
    * Checks that called function exists and that it matches it definition
    * @param ast CallExpr ast
    */
   VariableType returnTypeOfCallExpr(CallExprAST *ast);


   /**
    * Checks if a function has a valid return statement
    * @param ast   Function AST
    * @param typeB inferred return type
    */
   void checkForReturnType(std::ostream& os, FunctionAST *ast, VariableType typeB);


   /**
    * Checks if a used variable already exists in its symbol table
    * @param symbolTable symbol table of function
    * @param ast Identfier ast
    */
   void checkIfVariableIsDefined(std::ostream& os, SymbolTable *symbolTable, IdentifierAST *ast);


};

}

#endif //UNTITLED_SEMANTICCHECKS_H

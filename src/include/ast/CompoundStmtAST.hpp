#ifndef __COMPOUND_STMT_AST_HPP__
#define __COMPOUND_STMT_AST_HPP__

#include "StmtAST.hpp"
#include "StmtListAST.hpp"
#include "include/SemanticChecks.hpp"
#include "include/ast/CallExprAST.hpp"
#include "include/SymbolTable/SymbolTable.hpp"

/**
 * The AST class, which represents a compound statement
 */
namespace MC{
  class CompoundStmtAST: public StmtAST{
  private:
    StmtListAST_p branch;
    SymbolTable symbolTable;

  public:

    /**
     * Create a CompoundStmtAST tree, given a statement list
     * @param branch Statement list, which is within the compound statement
     * @param lineNumber line number in the code
     */
    CompoundStmtAST(StmtListAST_p branch, int lineNumber);
    ~CompoundStmtAST();

    /**
     * Creates a DOT note representation of the current node, which gets added to the parameter dot
     * @param dot dot tree where the current node should be added to
     */
    void generateDOT(DOTTree_p dot);

    /**
     * Traverses the tree in preOrder and executes function f on each compnent
     * @param f Funtion to call on each component.
     */
    void preOrder(std::function<void(AST*)> f);

    /**
     * Traverses the tree in postOrder and executes function f on each compnent
     * @param f Funtion to call on each component.
     */
    void postOrder(std::function<void(AST*)> f, bool deepTraversal);


    /**
     * Generates the symbol table and does semantic checks for the compound statement itself and all contained sub compound statements
     */
    VariableType semanticAnalysis(std::ostream& os);

    /**
     * Prints the symbol table for the compound statement itself and all contained sub compound statements
     * @param os outstream
     */
    std::ostream& printSymbolTable(std::string functionScope, std::ostream& os);

    /**
     * Merges the given symboltable into its own symboltable while maintaining shadowing
     * @param inTable [description]
     */
    void mergeSymbolTable(SymbolTable inTable);

    /**
     * Merges a parameter list into the symbol table
     * @param parameterList Parameter list to merg into the symbol table
     */
    void mergesParameterListIntoSymbolTable(std::ostream& os, std::vector<DeclarationStmtAST_p>* parameterList);


    /**
     * Generates the ICR for the ast
     * @param os Output stream
     */
    void generateICR(std::ostream&);

    /**
     * Checks if last statement is a return statment
     * @return is last statment a return statment
    */
    bool isLastStmtReturnStmt();
  };
}
#endif /* END __COMPOUND_STMT_AST_HPP__ */

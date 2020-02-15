#ifndef __STMT_LIST_AST_HPP__
#define __STMT_LIST_AST_HPP__

#include "AST.hpp"
#include "StmtAST.hpp"

/**
 * The AST class, which represents a statement
 */
namespace MC{
  class StmtListAST: public AST{
  private:
    std::vector<StmtAST_p> statementList;

  public:

    /**
     * Create an StmtListAST tree
     */
    StmtListAST();
    ~StmtListAST();

    /**
     * Adds a statement to the StmtListAST
    * @param statement Statment to add to the statment list
     */
    void addStatement(StmtAST_p statement);

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
     * Checks if last statement is a return statment
     * @return is last statment a return statment
     */
     bool isLastStmtReturnStmt();


    /**
     * Generates the ICR for the ast
     * @param os Output stream
     */
    void generateICR(std::ostream&);
  };
}

#endif /* END __STMT_LIST_AST_HPP__ */

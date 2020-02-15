#ifndef __ARGUMENTS_AST_HPP__
#define __ARGUMENTS_AST_HPP__

#include "AST.hpp"
#include "ExpressionAST.hpp"

/**
 * The AST class, which represents the arguemnts for a function call
 */
namespace MC{
  class ArgumentsAST: public AST{
  private:
    std::vector<ExpressionAST_p> argumentList;

  public:

    /**
     * Create an ArgumentsAST
     */
    ArgumentsAST();
    ~ArgumentsAST();

    /**
     * Adds an argument to the ArgumentsAST
     * @param expression Expression, which should be added to the argument list
     */
    void addArgument(ExpressionAST_p expression);

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

    std::vector<VariableTypeArray> getArguments();

    std::vector<std::string> getArgumentVariableList();


    /**
     * Generates the ICR for the ast
     * @param os Output stream
     */
      void generateICR(std::ostream&);
  };
}
#endif /* END __ARGUMENTS_AST_HPP__ */

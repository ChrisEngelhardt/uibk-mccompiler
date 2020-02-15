#ifndef __PARAMETERS_AST_HPP__
#define __PARAMETERS_AST_HPP__

#include "AST.hpp"
#include "DeclarationStmtAST.hpp"

/**
 * The AST class, which represents a parameter list
 */
namespace MC{
  class ParametersAST: public AST{
  private:
    std::vector<DeclarationStmtAST_p> parameterList;
  public:

    /**
     * Create an ParametersAST tree
     */
    ParametersAST();
    ~ParametersAST();



    /**
     * Adds a parameter to the ParametersAST
    * @param expression Declaration of a parameter
     */
    void addParameter(DeclarationStmtAST_p expression);

    /**
     * Returns the AST node as a string. This coresponds to the DOT node representation
     * @return the AST subtype as a string
     */
    std::string getAsString() const;

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
     * Returns the parameter list
     * @return parameter list
     */
    std::vector<DeclarationStmtAST_p>* getParameterList();


    /**
     * Generates the ICR for the ast
     * @param os Output stream
     */
      void generateICR(std::ostream&);

  };
}

#endif /* END __PARAMETERS_AST_HPP__ */

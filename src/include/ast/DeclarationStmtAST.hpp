#ifndef __DECLARATION_STMT_AST_HPP__
#define __DECLARATION_STMT_AST_HPP__

#include "IdentifierAST.hpp"
#include "IntLiteralAST.hpp"
#include "StmtAST.hpp"

/**
 * The AST class, which represents a declaration statement
 */
namespace MC{
  class DeclarationStmtAST: public StmtAST{
  private:
    VariableType variableType;
    IdentifierAST_p identifier;
    IntLiteralAST_p arraySize;

  public:

    /**
     * Create a DeclarationStmtAST tree, given a variable type and an identifer
     * @param variableType Type of the declaration given as a string
     * @param identifier Identifier of the declaration
     * @param lineNumber line number in the code
     */
    DeclarationStmtAST(std::string variableType, IdentifierAST_p identifier, int lineNumber);

    /**
     * Create a DeclarationStmtAST tree, given a variable type and an identifer and a array size.
     * @param variableType Type of the declaration given as a string
     * @param identifier Identifier of the declaration
     * @param arraySize Size of the array
     * @param lineNumber line number in the code
     */
    DeclarationStmtAST(std::string variableType, IdentifierAST_p identifier, IntLiteralAST_p arraySize, int lineNumber);
    ~DeclarationStmtAST();

    /**
     * Returns the AST node as a string. This coresponds to the DOT node representation
     * @return the AST subtype as a string
     */
    std::string getAsString() const;

    /**
     * Get identifier
     * @return identifier
     */
    std::string getIdentifier() const;

    /**
     * Get identifier
     * @return identifierAST
     */
    IdentifierAST_p getIdentifierAST();

    /**
     * Get type
     * @return type
     */
    VariableType getType() const;

    /**
     * Get array type
     * @return array type
     */
    VariableTypeArray getTypeArray() const;


    /**
     * Is the Declaration an array declaration?
     * @return is the declaration an array declaration
     */
    bool isArray() const;

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
     * Checks if the declaration is valid
     */
    void checkDeclaration();


    /**
     * Generates the ICR for the ast
     * @param os Output stream
     */
      void generateICR(std::ostream&);
  };
}

#endif /* END __DECLARATION_STMT_AST_HPP__ */

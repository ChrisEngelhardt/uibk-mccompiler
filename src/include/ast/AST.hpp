#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <memory>
#include "mcc/Exceptions.hpp"

#include "include/utils/DOTTree.hpp"
#include "include/mcScanner.hpp"
#include "include/ICR/ICRepresentation.hpp"

namespace MC{

  enum ASTTypes{
    expression, function, program, statement, statementL, arguments, parameters
  };

  enum VariableType{
    intType, floatType, stringType, boolType, voidType, undefined
  };

  struct VariableTypeArray{
    VariableType varType;
    long arraySize;

    VariableTypeArray(VariableType varType, long arraySize): varType(varType) , arraySize(arraySize){}
  };

  bool operator==(const VariableTypeArray& lhs, const VariableTypeArray& rhs);

  typedef std::shared_ptr<AST> AST_p;
  typedef std::shared_ptr<ArgumentsAST> ArgumentsAST_p;
  typedef std::shared_ptr<ArrayIdentifierAST> ArrayIdentifierAST_p;
  typedef std::shared_ptr<AssignmentStmtAST> AssignmentStmtAST_p;
  typedef std::shared_ptr<BinaryOpAST> BinaryOpAST_p;
  typedef std::shared_ptr<BoolLiteralAST> BoolLiteralAST_p;
  typedef std::shared_ptr<CallExprAST> CallExprAST_p;
  typedef std::shared_ptr<CompoundStmtAST> CompoundStmtAST_p;
  typedef std::shared_ptr<DeclarationStmtAST> DeclarationStmtAST_p;
  typedef std::shared_ptr<ExpressionAST> ExpressionAST_p;
  typedef std::shared_ptr<ExpressionStmtAST> ExpressionStmtAST_p;
  typedef std::shared_ptr<FloatLiteralAST> FloatLiteralAST_p;
  typedef std::shared_ptr<FunctionAST> FunctionAST_p;
  typedef std::shared_ptr<IdentifierAST> IdentifierAST_p;
  typedef std::shared_ptr<IfStmtAST> IfStmtAST_p;
  typedef std::shared_ptr<IntLiteralAST> IntLiteralAST_p;
  typedef std::shared_ptr<LiteralAST> LiteralAST_p;
  typedef std::shared_ptr<ParametersAST> ParametersAST_p;
  typedef std::shared_ptr<ProgramAST> ProgramAST_p;
  typedef std::shared_ptr<ReturnStmtAST> ReturnStmtAST_p;
  typedef std::shared_ptr<StmtAST> StmtAST_p;
  typedef std::shared_ptr<StmtListAST> StmtListAST_p;
  typedef std::shared_ptr<StringLiteralAST> StringLiteralAST_p;
  typedef std::shared_ptr<UnaryOpAST> UnaryOpAST_p;
  typedef std::shared_ptr<WhileStmtAST> WhileStmtAST_p;

  class IntLiteralAST;
  /**
   * The super class of the AST structure
   */




  class AST {
  private:
    ASTTypes astType;
    std::string astTypeString;

  protected:
    std::vector<AST_p> children;
    void setAstTypeString(std::string astTypeString);
    int lineNumber = -1;


  public:
      static VariableType getVariableTypeFromString(std::string variableType);
      static std::string getVariableTypeAsString(VariableType variableType);
      static std::string getVariableTypeAsString(VariableTypeArray variableType);




    enum TreeTraversal{
      postOrderType,
      preOrderType
    };

    /**
     * Create an AST tree, given the astType
     * @param astType type of the ast node
     */
    AST(ASTTypes astType);

    /**
     * Create an AST tree, given the astType
     * @param astType type of the ast node
     * @param lineNumber line number in the code
     */
    AST(ASTTypes astType, int lineNumber);
    virtual ~AST();

    /**
     * Overloading the << operator, to directly print the entry to an output stream
     */
    friend std::ostream& operator<<(std::ostream &os, const  AST& n);

    /**
     * Returns the AST subtype
     * @return the AST subtype as ASTType
     */
    ASTTypes getAstType();

    /**
     * Returns the AST subtype as a string
     * @return the AST subtype as a string
     */
    std::string getAstTypeAsString() const;

    /**
     * Returns the AST node as a string. This coresponds to the DOT node representation
     * e.g. FunctionAST as int gcm()
     * @return the AST subtype as a string
     */
    std::string getAsString() const;


    /**
     * Returns the line number which has created this ast in the parser
     * @return linenumber
     */
    int getLineNumber();


    /**
     * Creates a DOT note representation of the current node, which gets added to the parameter dot
     * @param dot dot tree where the current node should be added to
     */
    virtual void generateDOT(DOTTree_p dot);


    /**
     * Traverses the tree in preOrder and executes function f on each compnent
     * @param f Funtion to call on each component.
     */
    virtual void preOrder(std::function<void(AST*)> f);

    /**
     * Traverses the tree in postOrder and executes function f on each compnent
     * @param f Funtion to call on each component.
     */
    virtual void postOrder(std::function<void(AST*)> f, bool deepTraversal);

    /**
     * Generates the ICR for the ast
     * @param os Output stream
     */
    virtual void generateICR(std::ostream&) {};
  };



  template <class E>
  void isOfType(AST* ast, std::function<void(E*)> f){
    E* i = dynamic_cast<E*>(ast);
    if( i != NULL ){
      f(i);
    }
  }
}


#endif

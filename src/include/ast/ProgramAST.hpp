#ifndef __PROGRAM_AST_HPP__
#define __PROGRAM_AST_HPP__

#include "AST.hpp"
#include "FunctionAST.hpp"
#include "include/SemanticChecks.hpp"
#include "include/SymbolTable/FunctionTable.hpp"

/**
 * The AST class, which represents the entire program
 */
namespace MC{
  class ProgramAST: public AST{
  private:
    std::vector<FunctionAST_p> functionList;
    FunctionTable functionTable;

    void generateBuiltIns();
    void generateFunctionTable(std::ostream& os);
    void generateSymbolTable();
  public:

    /**
     * Create an ParametersAST tree
     */
    ProgramAST();
    ~ProgramAST();

    /**
     * Adds a funciont to the ParametersAST
    * @param function Function to add to the program
     */
    void addFunction(std::shared_ptr<FunctionAST> function);

    /**
     * Getter vor functionList
     * @return functionList
     */
    std::vector<FunctionAST_p>* getFunctionList();

    /**
     * Creates a DOT note representation of the current node, which gets added to the parameter dot
     * @param dot dot tree where the current node should be added to
     */
    void generateDOT(DOTTree_p dot);

    /**
     * Creates a DOT note representation of this node node
     */
    std::shared_ptr<DOTTree> getAsDot();

    /**
     * Creates a DOT note representation of a given function
     * @param function Name of the function as a string
     */
    std::shared_ptr<DOTTree>getAsDot(const std::string function);

    /**
     * Converts the symbol table for the whole programm to string
     * (must call semanticAnalysis() before)
     */
    std::ostream& getSymbolTable(std::ostream& os);

    /**
    * Converts the symbol table for the given function to string
    * (must call semanticAnalysis() before)
    * @param function Name of the function as a string
    */
    std::ostream& getSymbolTable(std::ostream& os, const std::string function);


    /**
     * Generates the symbol tables and checks for semantic errors
     */
    void semanticAnalysis(std::ostream& os, const std::string function);


    /**
     * Generates the ICR for the ast
     * @param os Output stream
     */
    void generateICR(std::ostream& os);

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
  };
}
#endif /* END __PROGRAM_AST_HPP__ */

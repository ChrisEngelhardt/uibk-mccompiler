#ifndef __MCC_HPP__
#define __MCC_HPP__

#include <cstddef>
#include <string>
#include <istream>

#include "../builddir/mcc@sha/parser.tab.hh"

namespace MC{

  class MCC{
  private:
    void parse_helper( std::istream &stream );
    MC::MC_Parser  *parser  = nullptr;
    MC::MC_Scanner *scanner = nullptr;

  public:

    // MC_Driver() = default;

    /**
    * root of our generated AST
    */
    std::shared_ptr<ProgramAST> ast = nullptr;

    virtual ~MCC();

    /**
    * Parse the given programm file
    * @param filename path to the program file
    */
    void parse( const char * const filename );

    /**
    * Parse the given input stream
    * @param iss input stream of the program to parse
    */
    void parse( std::istream &iss );


    /**
    * Generates the symbol tables and checks for semantic errors
    * @param os output stream for the trace
    */
    void semanticAnalysis(std::ostream& os);

    /**
    * Generates the symbol tables and checks for semantic errors
    * @param os output stream for the trace
    * @param function, which should be traced
    */
    void semanticAnalysis(std::ostream& os, const std::string function);

    /**
    * Generates the dot of the whole programm (must call parse before)
    * @return DOT as string
    */
    std::string getAsDot();

    /**
    * Generates the dot of the given function (must call parse before)
    * @param function name to generate dot for
    * @return DOT as string
    */
    std::string getAsDot(const std::string function);

    /**
    * Generates the symbol table of the whole progarm
    * @param os output stream for the trace
    * @return Symbol table as stream
    */
    std::ostream& getSymbolTable(std::ostream& os);

    /**
    * Generates the symbol table of the given function
    * @param os output stream for the trace
    * @param function function to generate the symbol table for
    * @return  Symbol table as stream
    */
    std::ostream& getSymbolTable(std::ostream& os, const std::string function);

    /**
    * Generates the intermediate code representation
    */
    void generateICR(std::ostream& os);

    /**
    * Returns the intermediate code representation
    * @param  function function to generate the symbol table for the given function
    * @return Intermediate code representation as stream
    */
    std::ostream& getICR(std::ostream& os, const std::string function = "");

    /**
    * Returns the CFG as DOT
    * @param  function function to generate the CFG for the given function
    * @return DOT as stream
    */
    std::ostream& getCFG(std::ostream& os, const std::string function = "");

    /**
     * Get the assembly code for specific function
     * @param  os       debug output stream
     * @param  asmOs    assembly stream
     * @param  name     name of the application
     * @param  function name of the function
     * @return          debug stream
     */
    std::ostream& getASM(std::ostream& os, std::ostream& asmOs, std::string name, const std::string function = "");

  };

} /* end namespace MC */
#endif /* END __MCC_HPP__ */

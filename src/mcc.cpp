#include <cassert>
#include <cctype>
#include <fstream>
#include <istream>

#include "mcc/mcc.hpp"

#include "include/astAll.hpp"
#include "include/mcScanner.hpp"
#include "include/ASM/ASMGenerator.hpp"

MC::MCC::~MCC(){
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
}

void MC::MCC::parse( const char * const filename ){
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( !in_file.good()){ throw(MCC_Exception("In File not good")); }
   parse_helper( in_file );
}

void MC::MCC::parse( std::istream &stream ){
   if( !stream.good() && stream.eof() ){ throw(MCC_Exception("Stream not good")); }
   parse_helper( stream );
}

void MC::MCC::parse_helper( std::istream &stream ){
  auto oldAST = ast;
  delete(scanner);
  try{
    scanner = new MC::MC_Scanner( &stream );
  }
  catch( std::bad_alloc &ba ){ throw(ba.what()); }

  delete(parser);
  parser = new MC::MC_Parser((*scanner), (*this));
  const int accept(0);
  if( parser->parse() != accept ){
    throw(MCC_Exception("Parse failed!!\n"));
  }

  if(oldAST != nullptr){
    for(auto function : *(ast->getFunctionList())){
      oldAST->addFunction(function);
    }
    ast = oldAST;
  }
}

void MC::MCC::semanticAnalysis(std::ostream& os){
  if(ast == nullptr){ throw(MCC_Exception("No parse tree")); }
  ast->semanticAnalysis(os,"");
}

void MC::MCC::semanticAnalysis(std::ostream& os, const std::string function){
  if(ast == nullptr){ throw(MCC_Exception("No parse tree")); }
  ast->semanticAnalysis(os,function);
}


void MC::MCC::generateICR(std::ostream& os){
  ast->generateICR(os);
}

std::ostream& MC::MCC::getICR(std::ostream& os, const std::string function){
  ICRepresentation::instance()->printContent(os, function);
  return os;
}

std::string MC::MCC::getAsDot(const std::string function){
    if(ast == nullptr){ throw(MCC_Exception("No parse tree")); }
    return ast->getAsDot(function)->getString();
}

std::string MC::MCC::getAsDot(){
  if(ast == nullptr){ throw(MCC_Exception("No parse tree")); }
  return ast->getAsDot()->getString();
}

std::ostream& MC::MCC::getSymbolTable(std::ostream& os, const std::string function){
  if(ast == nullptr){ throw(MCC_Exception("No parse tree")); }
  return ast->getSymbolTable(os, function);
}

std::ostream& MC::MCC::getSymbolTable(std::ostream& os){
  if(ast == nullptr){ throw(MCC_Exception("No parse tree")); }
  return ast->getSymbolTable(os);
}

std::ostream& MC::MCC::getCFG(std::ostream& os, const std::string function){
  return ICRepresentation::instance()->generateCFG(os,function);
}

std::ostream& MC::MCC::getASM(std::ostream& os, std::ostream& asmOs, std::string name, const std::string function){
  return ASMGenerator::generate(ICRepresentation::instance()->getICRList(), os, asmOs, name, function);
}

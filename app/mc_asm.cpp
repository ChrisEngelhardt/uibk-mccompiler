#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "mcc/Exceptions.hpp"
#include "mcc/mcc.hpp"
#include "../app/include/ArgumentParser.hpp"
#include "../app/include/MCCCommon.hpp"

using namespace MC;

void printHelpMessage(){
  std::cout << "usage: mc_asm [OPTIONS] file...\n\n"
  "Utility for printing the generated assembly code. Errors are reported on\n"
  "invalid inputs.\n\n"
  "Use '-' as input file to read from stdin.\n\n"
  "OPTIONS:\n"
  "  -h, --help                displays this help message\n"
  "  -o, --output <file>       write the output to <file> (defaults to stdout)\n"
  "  -f, --function <name>     limit scope to the given function\n"
 << std::endl;
}

int main( const int argc, const char **argv ){
  ArgumentParser arg(argc, argv);

  //If no input is provieded or the -h flag, print help
  if( argc <= 1 || arg.cmdOptionExists("-h")){
    printHelpMessage();
    return ( EXIT_SUCCESS );
  }

  MC::MCC mcc;
  try{
    int cntInFiles = arg.numberOfFiles({"-h", "-o", "-f"});
    for (int i = cntInFiles; i>0; i--){
      mcc.parse( argv[argc - i]);
    }

    std::ostringstream osTmp;
    mcc.semanticAnalysis(osTmp);
    mcc.generateICR(osTmp);
    mcc.getICR(osTmp);
    std::ostringstream os;

    arg.cmdOptionExists("-f") ? mcc.getASM(osTmp, os, argv[argc - 1], arg.getCmdOption("-f")) : mcc.getASM(osTmp, os, argv[argc - 1]);
    if (!arg.cmdOptionExists("-o")){
      std::cout << os.str();
    }else{
      writeToFile(arg.getCmdOption("-o"), os.str());
    }
  }catch (Semantic_Exception e){
    std::cout << "Semantic error: "  << e.what() << std::endl;
    return EXIT_FAILURE;
  }


  return( EXIT_SUCCESS );
}

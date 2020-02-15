#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "mcc/Exceptions.hpp"
#include "mcc/mcc.hpp"
#include "../app/include/StringUtils.hpp"
#include "../app/include/ArgumentParser.hpp"
#include "../app/include/MCCCommon.hpp"

#define VERSION "0.1"
#define COMMANDBUFFERSIZE 512
#define STDMCLIBPATH "../data"
#define STDMCLIBNAMEC "stdmclib.c"
#define STDMCLIBNAMEO "stdmclib.o"
#define DEFAULTOUTPATH "."
#define ENV_VAR_BACKEND "MCC_BACKEND"

using namespace MC;

void printHelpMessage(){
  std::cout <<  "usage: mcc [OPTIONS] file...\n\n"
                "The mC compiler. It takes mC input files and produces an executable.\n\n"
                "Use '-' as input file to read from stdin.\n\n"
                "OPTIONS:\n"
                "-h, --help                displays this help message\n"
                "-v, --version             displays the version number\n"
                "-q, --quiet               suppress error output\n"
                "-o, --output <file>       write the output to <file> (defaults to 'a.out')\n\n"
                "Environment Variables:\n"
                "MCC_BACKEND               override the back-end compiler (defaults to 'gcc' in PATH)\n" << std::endl;
}

void printVersion(){
  std::cout <<  "mc compiler Version " << VERSION  << std::endl;
}

int compile(std::string basePath, std::string inFile, std::string outFile, bool quiet){
    char command[COMMANDBUFFERSIZE];

  const char* backend = std::getenv(ENV_VAR_BACKEND) != NULL ? std::getenv("PATH") : "gcc";
    snprintf(command, COMMANDBUFFERSIZE, "%s -m32 -c %s/%s -o %s/%s", backend, basePath.c_str(), inFile.c_str(), DEFAULTOUTPATH,
             outFile.c_str());
  if (!quiet){
    std::cout<<command<<"\n";
  }
    return system(command);
}

int link(std::string mcFile, std::string buildInFile, std::string outFile, bool quiet){
    char command[COMMANDBUFFERSIZE];
  const char* backend = std::getenv(ENV_VAR_BACKEND) != NULL ? std::getenv("PATH") : "gcc";
    snprintf(command, COMMANDBUFFERSIZE, "%s -m32 %s %s -o %s", backend, mcFile.c_str(), buildInFile.c_str(), outFile.c_str());
  if (!quiet){
    std::cout<<command<<"\n";
  }
  return system(command);
}

int main( const int argc, const char **argv ){
  ArgumentParser arg(argc, argv);
  bool quiet = arg.cmdOptionExists("-q");

  //If no input is provieded or the -h flag, print help
  if( argc <= 1 || arg.cmdOptionExists("-h")){
    printHelpMessage();
    return ( EXIT_SUCCESS );
  }

  if( argc <= 1 || arg.cmdOptionExists("-v")){
    printVersion();
    return ( EXIT_SUCCESS );
  }

  std::string outfile = arg.cmdOptionExists("-o") ? arg.getCmdOption("-o") : "out";

  MC::MCC mcc;
  try{
    std::ostringstream os;
    std::ostringstream osTmp;

    //For each file, parse content
    int cntInFiles = arg.numberOfFiles({"-h", "-v", "-q", "-o"});
    for (int i = cntInFiles; i>0; i--){
      mcc.parse( argv[argc - i]);
    }
    mcc.semanticAnalysis(osTmp);

    mcc.generateICR(osTmp);
    mcc.getASM(osTmp, os, argv[argc - cntInFiles]);
    std::string programmName = basenameMC(argv[argc - cntInFiles]);
    writeToFile(programmName +".s", os.str());

    //Compile build-ins and mc assembly
    if ((compile(STDMCLIBPATH, STDMCLIBNAMEC, STDMCLIBNAMEO, quiet) + compile(".", programmName+".s", programmName+".o", quiet)) == 0){
      link(programmName+".o", STDMCLIBNAMEO,  outfile, quiet);
    }

  }catch (Semantic_Exception e){
    if (!quiet){
      std::cout << "Semantic error: "  << e.what() << std::endl;
    }
    return EXIT_FAILURE;
  }

  return( EXIT_SUCCESS );
}

#include <fstream>
#include <iostream>

#include <gtest/gtest.h>

#include "mcc/Exceptions.hpp"
#include "mcc/mcc.hpp"

struct MCAssemblyTest : ::testing::Test{
    MC::MCC *mcc;

    MCAssemblyTest(){
        mcc = new MC::MCC();
    }

    ~MCAssemblyTest(){
        delete(mcc);
    }
};

TEST_F(MCAssemblyTest, getASMWithoutAnything){
    //GIVEN
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "fib";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //THEN
    mcc->getASM(os,asmOs,name);

    //Empty target
    ASSERT_STRCASEEQ("", os.str().c_str());
}

TEST_F(MCAssemblyTest, getASMAfterParse){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "fib";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);

    //THEN
    mcc->getASM(os,asmOs,name);

    //Empty target
    ASSERT_STRCASEEQ("", os.str().c_str());
}

TEST_F(MCAssemblyTest, getASMAfterSemanticAnalysis){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "fib";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);

    //THEN
    mcc->getASM(os,asmOs,name);

    //Doubtful output
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCAssemblyTest, multipleFilesAssembly){
    //GIVEN
    const char *input = "../test/unit/multipleFilesLeapYear/multipleFilesLeapYear.mc";
    const char *input2 = "../test/unit/multipleFilesLeapYear/multipleFilesLeapYear2.mc";
    const char *input3 = "../test/unit/multipleFilesLeapYear/multipleFilesLeapYear3.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "leap_year";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);
    mcc->parse(input2);
    mcc->parse(input3);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);

    //THEN
    mcc->getASM(os,asmOs,name);

    ASSERT_LE(os.str().find("isLeapYear"),os.str().length());
    ASSERT_LE(os.str().find("modulo"),os.str().length());
    ASSERT_LE(os.str().find("main"),os.str().length());
    ASSERT_LE(os.str().find("int"),os.str().length());
    ASSERT_LE(os.str().find("bool"),os.str().length());
    ASSERT_LE(os.str().find("string"),os.str().length());
    ASSERT_LE(os.str().find("if"),os.str().length());
    ASSERT_LE(os.str().find("while"),os.str().length());
    ASSERT_LE(os.str().find("Return"),os.str().length());
}

TEST_F(MCAssemblyTest, binarySearchAssembly){
    //GIVEN
    const char *input = "../test/integration/binarySearch/binarySearch.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "binary_search";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);

    //THEN
    mcc->getASM(os,asmOs,name);

    ASSERT_LE(os.str().find("binary_search"),os.str().length());
    ASSERT_LE(os.str().find("main"),os.str().length());
    ASSERT_LE(os.str().find("int"),os.str().length());
    ASSERT_LE(os.str().find("bool"),os.str().length());
    ASSERT_LE(os.str().find("string"),os.str().length());
    ASSERT_LE(os.str().find("while"),os.str().length());
    ASSERT_LE(os.str().find("Return"),os.str().length());
}

TEST_F(MCAssemblyTest, emptyAssembly){
    //GIVEN
    const char *input = "../test/integration/empty/empty.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "empty";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);

    //THEN
    mcc->getASM(os,asmOs,name);

    ASSERT_LE(os.str().find("main"),os.str().length());
    ASSERT_LE(os.str().find("int"),os.str().length());
    ASSERT_LE(os.str().find("Return"),os.str().length());
}

TEST_F(MCAssemblyTest, femAssembly){
    //GIVEN
    const char *input = "../test/integration/fem/fem.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "fem";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);

    //THEN
    mcc->getASM(os,asmOs,name);

    ASSERT_LE(os.str().find("main"),os.str().length());
    ASSERT_LE(os.str().find("int"),os.str().length());
    ASSERT_LE(os.str().find("float"),os.str().length());
    ASSERT_LE(os.str().find("string"),os.str().length());
    ASSERT_LE(os.str().find("while"),os.str().length());
    ASSERT_LE(os.str().find("if"),os.str().length());
    ASSERT_LE(os.str().find("Return"),os.str().length());
}

TEST_F(MCAssemblyTest, fibAssembly){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "fib";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);

    //THEN
    mcc->getASM(os,asmOs,name);

    ASSERT_LE(os.str().find("fib"),os.str().length());
    ASSERT_LE(os.str().find("main"),os.str().length());
    ASSERT_LE(os.str().find("int"),os.str().length());
    ASSERT_LE(os.str().find("string"),os.str().length());
    ASSERT_LE(os.str().find("if"),os.str().length());
    ASSERT_LE(os.str().find("Return"),os.str().length());
}

TEST_F(MCAssemblyTest, leapYearAssembly){
    //GIVEN
    const char *input = "../test/integration/leapYear/leapYear.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "leap_year";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);

    //THEN
    mcc->getASM(os,asmOs,name);

    ASSERT_LE(os.str().find("isLeapYear"),os.str().length());
    ASSERT_LE(os.str().find("modulo"),os.str().length());
    ASSERT_LE(os.str().find("main"),os.str().length());
    ASSERT_LE(os.str().find("int"),os.str().length());
    ASSERT_LE(os.str().find("bool"),os.str().length());
    ASSERT_LE(os.str().find("string"),os.str().length());
    ASSERT_LE(os.str().find("if"),os.str().length());
    ASSERT_LE(os.str().find("while"),os.str().length());
    ASSERT_LE(os.str().find("Return"),os.str().length());
}

TEST_F(MCAssemblyTest, leibnizPiAssembly){
    //GIVEN
    const char *input = "../test/integration/leibnizPi/leibnizPi.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "leibniz_pi";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);

    //THEN
    mcc->getASM(os,asmOs,name);

    ASSERT_LE(os.str().find("kth"),os.str().length());
    ASSERT_LE(os.str().find("main"),os.str().length());
    ASSERT_LE(os.str().find("float"),os.str().length());
    ASSERT_LE(os.str().find("string"),os.str().length());
    ASSERT_LE(os.str().find("while"),os.str().length());
    ASSERT_LE(os.str().find("Return"),os.str().length());
}

TEST_F(MCAssemblyTest, mandelbrotAssembly){
    //GIVEN
    const char *input = "../test/integration/mandelbrot/mandelbrot.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "mandelbrot";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);

    //THEN
    mcc->getASM(os,asmOs,name);

    ASSERT_LE(os.str().find("transform_x"),os.str().length());
    ASSERT_LE(os.str().find("transform_y"),os.str().length());
    ASSERT_LE(os.str().find("is_in_set"),os.str().length());
    ASSERT_LE(os.str().find("main"),os.str().length());
    ASSERT_LE(os.str().find("int"),os.str().length());
    ASSERT_LE(os.str().find("float"),os.str().length());
    ASSERT_LE(os.str().find("bool"),os.str().length());
    ASSERT_LE(os.str().find("string"),os.str().length());
    ASSERT_LE(os.str().find("if"),os.str().length());
    ASSERT_LE(os.str().find("while"),os.str().length());
    ASSERT_LE(os.str().find("Return"),os.str().length());
}

TEST_F(MCAssemblyTest, numberGuessingAssembly){
    //GIVEN
    const char *input = "../test/integration/numberGuessing/numberGuessing.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "number_guessing";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);

    //THEN
    mcc->getASM(os,asmOs,name);

    ASSERT_LE(os.str().find("guessNumber"),os.str().length());
    ASSERT_LE(os.str().find("main"),os.str().length());
    ASSERT_LE(os.str().find("int"),os.str().length());
    ASSERT_LE(os.str().find("bool"),os.str().length());
    ASSERT_LE(os.str().find("void"),os.str().length());
    ASSERT_LE(os.str().find("string"),os.str().length());
    ASSERT_LE(os.str().find("if"),os.str().length());
    ASSERT_LE(os.str().find("while"),os.str().length());
    ASSERT_LE(os.str().find("Return"),os.str().length());
}

TEST_F(MCAssemblyTest, primeAssembly){
    //GIVEN
    const char *input = "../test/integration/prime/prime.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "prime";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);

    //THEN
    mcc->getASM(os,asmOs,name);

    ASSERT_LE(os.str().find("is_prime"),os.str().length());
    ASSERT_LE(os.str().find("main"),os.str().length());
    ASSERT_LE(os.str().find("int"),os.str().length());
    ASSERT_LE(os.str().find("string"),os.str().length());
    ASSERT_LE(os.str().find("if"),os.str().length());
    ASSERT_LE(os.str().find("while"),os.str().length());
    ASSERT_LE(os.str().find("Return"),os.str().length());
}

TEST_F(MCAssemblyTest, sortingNetworkAssembly){
    //GIVEN
    const char *input = "../test/integration/sortingNetwork/sortingNetwork.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "sorting_network";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);

    //THEN
    mcc->getASM(os,asmOs,name);

    ASSERT_LE(os.str().find("sort"),os.str().length());
    ASSERT_LE(os.str().find("main"),os.str().length());
    ASSERT_LE(os.str().find("int"),os.str().length());
    ASSERT_LE(os.str().find("void"),os.str().length());
    ASSERT_LE(os.str().find("string"),os.str().length());
    ASSERT_LE(os.str().find("if"),os.str().length());
    ASSERT_LE(os.str().find("Return"),os.str().length());
}

TEST_F(MCAssemblyTest, subsetSumAssembly){
    //GIVEN
    const char *input = "../test/integration/subsetSum/subsetSum.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "subset_sum";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);

    //THEN
    mcc->getASM(os,asmOs,name);

    ASSERT_LE(os.str().find("is_subset_sum"),os.str().length());
    ASSERT_LE(os.str().find("main"),os.str().length());
    ASSERT_LE(os.str().find("int"),os.str().length());
    ASSERT_LE(os.str().find("bool"),os.str().length());
    ASSERT_LE(os.str().find("string"),os.str().length());
    ASSERT_LE(os.str().find("if"),os.str().length());
    ASSERT_LE(os.str().find("while"),os.str().length());
    ASSERT_LE(os.str().find("Return"),os.str().length());
}

TEST_F(MCAssemblyTest, taylorAssembly){
    //GIVEN
    const char *input = "../test/integration/taylor/taylor.mc";
    std::ostringstream os;
    std::ostringstream asmOs;
    std::string name = "taylor";
    std::string entrypoint = "main";
    asmOs << "\t.file \"" << name << "\"\n" ;
    asmOs << "\t.text\n";
    asmOs << "\t.globl " << entrypoint << "\n";
    asmOs << "\t.type " << entrypoint << ", @function\n";

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->generateICR(os);

    //THEN
    mcc->getASM(os,asmOs,name);

    ASSERT_LE(os.str().find("taylor_approx"),os.str().length());
    ASSERT_LE(os.str().find("main"),os.str().length());
    ASSERT_LE(os.str().find("int"),os.str().length());
    ASSERT_LE(os.str().find("float"),os.str().length());
    ASSERT_LE(os.str().find("string"),os.str().length());
    ASSERT_LE(os.str().find("while"),os.str().length());
    ASSERT_LE(os.str().find("Return"),os.str().length());
}

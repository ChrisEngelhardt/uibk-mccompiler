#include <fstream>
#include <iostream>

#include <gtest/gtest.h>

#include "mcc/Exceptions.hpp"
#include "mcc/mcc.hpp"


struct MCSemanticTest : ::testing::Test{
    MC::MCC *mcc;

    MCSemanticTest(){
        mcc = new MC::MCC();
    }

    ~MCSemanticTest(){
        delete(mcc);
    }
};

TEST_F(MCSemanticTest, SymbolTableBeforeSemanticAnalysis){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    const char *func = "";
    std::ostringstream os;

    //WHEN
    mcc->parse(input);

    //THEN
    EXPECT_THROW(mcc->getSymbolTable(os,func), MC::MCC_Exception);
}

TEST_F(MCSemanticTest, SymbolTableFromInvalidFunction){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    const char *func = "NOTAVALIDFUNCTION";
    std::ostringstream os;

    //WHEN
    mcc->parse(input);
    mcc->semanticAnalysis(os);

    //THEN
    EXPECT_THROW(mcc->getSymbolTable(os,func), MC::MCC_Exception);
}

TEST_F(MCSemanticTest, DefiningVariableTwice){
    //GIVEN
    const char *input = "../test/unit/shadowingSameInt/shadowingSameInt.mc";
    std::ostringstream os;
    const char *func = "main";

    //DURING
    mcc->parse(input);

    //THEN
    EXPECT_THROW(mcc->semanticAnalysis(os, func), Semantic_Exception);
}

TEST_F(MCSemanticTest, SymbolTableFromFunctionMain){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    std::ostringstream os;
    const char *func = "main";

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os, func);
    mcc->getSymbolTable(os, func);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCSemanticTest, multipleFilesSemantic){
    //GIVEN
    const char *input = "../test/unit/multipleFilesLeapYear/multipleFilesLeapYear.mc";
    const char *input2 = "../test/unit/multipleFilesLeapYear/multipleFilesLeapYear2.mc";
    const char *input3 = "../test/unit/multipleFilesLeapYear/multipleFilesLeapYear3.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->parse(input2);
    mcc->parse(input3);
    mcc->semanticAnalysis(os);
    mcc->getSymbolTable(os);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCSemanticTest, binarySearchSemantic){
    //GIVEN
    const char *input = "../test/integration/binarySearch/binarySearch.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->getSymbolTable(os);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCSemanticTest, emptySemantic){
    //GIVEN
    const char *input = "../test/integration/empty/empty.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->getSymbolTable(os);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCSemanticTest, femSemantic){
    //GIVEN
    const char *input = "../test/integration/fem/fem.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->getSymbolTable(os);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCSemanticTest, fibSemantic){
    //GIVEN
    const char *input = "../test/integration/fib/fib.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->getSymbolTable(os);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCSemanticTest, leapYearSemantic){
    //GIVEN
    const char *input = "../test/integration/leapYear/leapYear.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->getSymbolTable(os);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCSemanticTest, leibnizPiSemantic){
    //GIVEN
    const char *input = "../test/integration/leibnizPi/leibnizPi.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->getSymbolTable(os);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCSemanticTest, lucasNumberSemantic){
    //GIVEN
    const char *input = "../test/integration/lucasNumber/lucasNumber.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->getSymbolTable(os);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCSemanticTest, mandelbrotSemantic){
    //GIVEN
    const char *input = "../test/integration/mandelbrot/mandelbrot.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->getSymbolTable(os);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCSemanticTest, numberGuessingSemantic){
    //GIVEN
    const char *input = "../test/integration/numberGuessing/numberGuessing.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->getSymbolTable(os);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCSemanticTest, primeSemantic){
    //GIVEN
    const char *input = "../test/integration/prime/prime.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->getSymbolTable(os);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCSemanticTest, sortingNetworkSemantic){
    //GIVEN
    const char *input = "../test/integration/sortingNetwork/sortingNetwork.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->getSymbolTable(os);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCSemanticTest, subsetSum){
    //GIVEN
    const char *input = "../test/integration/subsetSum/subsetSum.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->getSymbolTable(os);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}

TEST_F(MCSemanticTest, taylorSemantic){
    //GIVEN
    const char *input = "../test/integration/taylor/taylor.mc";
    std::ostringstream os;

    //DURING
    mcc->parse(input);
    mcc->semanticAnalysis(os);
    mcc->getSymbolTable(os);

    //THEN
    ASSERT_STRCASENE("", os.str().c_str());
}
